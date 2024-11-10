#include "scene/scene.hpp"

#include "core/logger.hpp"
#include "flecs.h"

#include "flecs/addons/cpp/mixins/rest/decl.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "graphics/render2d.hpp"
#include "scene/component.hpp"
#include "asset/scene_asset.hpp"

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
        asset->write();
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
            .set<component::sprite>({
                .texture = graphics::texture2d::load(
                    "C:/Users/User/Downloads/narechi-test/"
                    "assets/rockett-young-pixel-lulu.png",
                    {}),
            });
    }

    void scene::save()
    {
        asset->write();
    }

    std::string scene::get_name() const
    {
        return data->name;
    }
}