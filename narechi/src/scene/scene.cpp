#include "scene/scene.hpp"

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

    sptr<scene> scene::load(const std::filesystem::path& path)
    {
        sptr<scene> existing_scene = make_sptr<scene>(path);
        existing_scene->data->world.import <component>();
        existing_scene->data->world.set<flecs::Rest>({});
        existing_scene->asset->load();

        return existing_scene;
    }

    sptr<scene> scene::load(uptr<asset::scene_asset> scene_asset)
    {
        sptr<scene> existing_scene = make_sptr<scene>();
        existing_scene->asset = std::move(scene_asset);
        existing_scene->asset->to_owned(existing_scene->data);

        // To load the world
        existing_scene->data->world.import <component>();
        existing_scene->data->world.set<flecs::Rest>({});
        existing_scene->asset->load(true);
        return existing_scene;
    }

    void scene::awake()
    {
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

    void scene::add_entity()
    {
        data->world.entity()
            .add<component::position>()
            .add<component::meta>()
            .set<component::sprite>({ .texture_asset_guid
                = "3df4409a-981f-41d5-9fc4-2b610f83ed33" });
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
                std::filesystem::path image_build_asset_path
                    = dir / (image_asset_path.filename());
                if (std::filesystem::exists(image_build_asset_path))
                {
                    std::filesystem::remove(image_build_asset_path);
                }
                std::filesystem::copy_file(
                    image_asset_path, image_build_asset_path);
            });
    }

    std::string scene::get_name() const
    {
        return data->name;
    }
}