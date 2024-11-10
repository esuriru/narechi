#pragma once

#include "core/logger.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "graphics/texture2d.hpp"
#include "graphics/render2d.hpp"

#include "flecs.h"

namespace narechi::scene
{
    struct component
    {
        struct position
        {
            glm::vec2 value = glm::vec2(0.0f, 0.0f);
        };

        struct scene_camera
        {
        };

        struct meta
        {
        };

        struct sprite
        {
            sptr<graphics::texture2d> texture;
        };

        component(flecs::world& world)
        {
            // world.module<component>();
            world.component<glm::vec2>()
                .member("x", &glm::vec2::x)
                .member("y", &glm::vec2::y);
            world.component<position>().member<glm::vec2>("value");
            world.component<sprite>();
            world.component<scene_camera>();
            world.component<meta>();

            flecs::system sprite_render_system
                = world
                      .system<const component::position,
                          const component::sprite>("SpriteRender")
                      .kind(flecs::OnUpdate)
                      .each(
                          [](const component::position& pos,
                              const component::sprite& sprite)
                          {
                              graphics::render2d::submit_quad(
                                  pos.value, { 20, 20 }, sprite.texture);
                          });

            flecs::system camera_update_view_system
                = world
                      .system<const component::position,
                          component::scene_camera>("UpdateViewMatrix")
                      .kind(flecs::OnUpdate)
                      .each(
                          [&](const component::position& position,
                              component::scene_camera)
                          {
                              static glm::vec2 debug_pos {};
                              static float elapsed_time;

                              elapsed_time += world.delta_time();
                              debug_pos.x = sinf(elapsed_time);

                              graphics::render2d::set_view_matrix(
                                  glm::inverse(glm::translate(glm::mat4(1.0f),
                                      glm::vec3(debug_pos, 0.0f))));
                          });
        }
    };
}