#include "scene/scene.hpp"

#include "flecs.h"

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
        return existing_scene;
    }

    void scene::awake()
    {
        auto& world = data->world;

        flecs::query<const position, scene_camera> camera_query
            = world.query<const position, scene_camera>();
        if (camera_query.count() == 0)
        {
            world.entity().add<position>().add<scene_camera>();
        }

        flecs::system sprite_render_system
            = data->world.system<const position, const sprite>("SpriteRender")
                  .each(
                      [](const position& pos, const sprite& sprite)
                      {
                          graphics::render2d::submit_quad(
                              pos.value, sprite.texture);
                      });

        camera_query.each(
            [](const position& position, scene_camera)
            {
                graphics::render2d::set_view_matrix(glm::inverse(glm::translate(
                    glm::mat4(1.0f), glm::vec3(position.value, 0))));
            });
    }

    void scene::update(float delta_time)
    {
        data->world.progress(delta_time);
    }

    void scene::add_entity()
    {
        data->world.entity().add<position>().add<sprite>();
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