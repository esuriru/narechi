#include "scene/scene.hpp"

#include "core/logger.hpp"
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
                              pos.value, { 20, 20 }, sprite.texture);
                      });

        flecs::system camera_update_view_system
            = data->world
                  .system<const position, scene_camera>("UpdateViewMatrix")
                  .each(
                      [this](const position& position, scene_camera)
                      {
                          static glm::vec2 debug_pos {};
                          static float elapsed_time;

                          elapsed_time += data->world.delta_time();
                          debug_pos.x = sinf(elapsed_time);

                          //   const glm::vec3 world_position { debug_pos, 0.0f
                          //   }; graphics::render2d::set_view_matrix(
                          //       glm::lookAt(world_position,
                          //           world_position + glm::vec3(0.0f, 0.0f,
                          //           -1.0f), { 0.0f, 1.0f, 0.0f }));

                          graphics::render2d::set_view_matrix(
                              glm::inverse(glm::translate(glm::mat4(1.0f),
                                  glm::vec3(debug_pos, 0.0f))));
                      });
    }

    void scene::update(float delta_time)
    {
        data->world.progress(delta_time);
    }

    void scene::add_entity()
    {
        data->world.entity().add<position>().set<sprite>({ .texture
            = graphics::texture2d::load("C:/Users/User/Downloads/narechi-test/"
                                        "assets/rockett-young-pixel-lulu.png",
                {}) });
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