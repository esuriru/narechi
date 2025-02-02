#include "scene/scene.hpp"

#include "asset/lua_script_meta_asset.hpp"
#include "core/logger.hpp"
#include "flecs.h"

#include "flecs/addons/cpp/mixins/rest/decl.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "graphics/render2d.hpp"
#include "scene/component.hpp"
#include "asset/scene_asset.hpp"
#include "asset/asset_extensions.hpp"
#include <filesystem>

namespace narechi::scene
{
    scene::scene()
        : data(nullptr)
        , asset(nullptr)
    {
    }

    scene::scene(const std::filesystem::path& path)
        : data(make_uptr<scene::scene_data>())
        , asset(make_uptr<asset::scene_asset>(path, data.get()))
    {
        data->world.import <component>();
    }

    scene::~scene()
    {
        asset.reset();
        data->world.release();
    }

    sptr<scene> scene::create(
        const std::filesystem::path& path, const std::string& name)
    {
        sptr<scene> new_scene = make_sptr<scene>(path);
        new_scene->data->name = name;
        new_scene->save();
        return new_scene;
    }

    sptr<scene> scene::load(const std::filesystem::path& path,
        sptr<asset::component_def_asset> cdef)
    {
        sptr<scene> existing_scene = make_sptr<scene>(path);
        existing_scene->data->world.import <component>();

        // Run component definition scripts
        constexpr const char* script_name = "User-defined components";
        if (cdef && existing_scene->data->world.lookup(script_name) == 0)
        {
            // Import user-defined components
            // world.script("User-defined components")
            //     .code(component_def_asset->get_code().c_str())
            //     .run();
            existing_scene->data->world.entity(script_name);
            ecs_script_run(existing_scene->data->world,
                script_name,
                cdef->get_code().c_str());
        }

        existing_scene->data->world.set<flecs::Rest>({});
        existing_scene->asset->load();

        return existing_scene;
    }

    sptr<scene> scene::load(uptr<asset::scene_asset> scene_asset,
        sptr<asset::component_def_asset> cdef)
    {
        sptr<scene> existing_scene = make_sptr<scene>();
        existing_scene->asset = std::move(scene_asset);
        existing_scene->asset->to_owned(existing_scene->data);

        // To load the world
        existing_scene->data->world.import <component>();

        // Run component definition scripts
        constexpr const char* script_name = "User-defined components";
        if (cdef && existing_scene->data->world.lookup(script_name) == 0)
        {
            // Import user-defined components
            // world.script("User-defined components")
            //     .code(component_def_asset->get_code().c_str())
            //     .run();
            existing_scene->data->world.entity(script_name);
            ecs_script_run(existing_scene->data->world,
                script_name,
                cdef->get_code().c_str());
        }

        existing_scene->data->world.set<flecs::Rest>({});
        existing_scene->asset->load(true);
        return existing_scene;
    }

    void scene::awake()
    {
        // data->world.script("User-defined components")
        //     .code(R"(
        //     using flecs.meta;

        //     struct scale {
        //         x = f32
        //         y = f32
        //     }
        //     )")
        //     .run();

        // ecs_script_run(data->world, "User-defined components", R"(
        //     using flecs.meta;

        //     struct scale {
        //         x = f32
        //         y = f32
        //     }
        //     )");

        if (!data->world.lookup("SceneCamera"))
        {
            NRC_CORE_INFO("Created SceneCamera because there is none");
            data->world.entity("SceneCamera")
                .add<component::meta>()
                .add<component::position>()
                .add<component::scene_camera>();
        }
    }

    void scene::update(float delta_time)
    {
        data->world.progress(delta_time);
    }

    void scene::add_entity(const std::string& name)
    {
        data->world.entity(name.c_str()).add<component::meta>();
    }

    void scene::add_empty_sprite(const std::string& name)
    {
        data->world.entity(name.c_str())
            .add<component::position>()
            .add<component::meta>()
            .add<component::sprite>();
    }

    void scene::save()
    {
        asset->write();
    }

    void scene::export_to_dir(const std::filesystem::path& dir, bool save)
    {
        if (save)
        {
            this->save();
        }

        using namespace asset;
        asset->write(dir / (get_name() + extension<scene_asset>::value));

        auto copy_file = [dir](const std::filesystem::path& path)
        {
            NRC_ASSERT(std::filesystem::exists(path),
                "Path does not exist when copying: ",
                path);

            // Have to manually delete because exception throws
            std::filesystem::path target_path = dir / path.filename();
            if (std::filesystem::exists(target_path))
            {
                std::filesystem::remove(target_path);
            }

            std::filesystem::copy(path,
                target_path,
                std::filesystem::copy_options::overwrite_existing);
        };

        // Export sprites
        data->world.query<const component::sprite>().each(
            [&](const component::sprite& sprite)
            {
                // Copy sprite asset
                sptr<sprite_asset> scene_sprite_asset
                    = app::get().get_asset_database().get_asset<sprite_asset>(
                        sprite.texture_asset_guid);
                scene_sprite_asset->write(
                    dir / (scene_sprite_asset->get_path().filename()));

                std::filesystem::path image_asset_path
                    = scene_sprite_asset->get_path();
                image_asset_path.replace_extension(".png");

                // Copy actual image, replace if exists
                copy_file(image_asset_path);
            });

        data->world.query<const component::lua_script>().each(
            [&](const component::lua_script& script)
            {
                sptr<lua_script_meta_asset> script_meta_asset
                    = app::get()
                          .get_asset_database()
                          .get_asset<lua_script_meta_asset>(
                              script.script_asset_guid);
                script_meta_asset->write(
                    dir / (script_meta_asset->get_path().filename()));

                std::filesystem::path script_path
                    = script_meta_asset->get_path();
                script_path.replace_extension(script::lua_script::extension());

                copy_file(script_path);
            });
    }

    std::string scene::get_name() const
    {
        return data->name;
    }

    flecs::world scene::get_world() const
    {
        return data->world;
    }
}