#pragma once

#include "asset/sprite_asset.hpp"
#include "core/app.hpp"
#include "core/logger.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "graphics/texture2d.hpp"
#include "graphics/render2d.hpp"
#include "graphics/render_command.hpp"

#include "flecs.h"

namespace narechi::scene
{
    struct component
    {
        struct position
        {
            glm::vec2 value = glm::vec2(0.0f, 0.0f);
        };

        struct scale
        {
            glm::vec2 value = glm::vec2(1.0f, 1.0f);
        };

        struct scene_camera
        {
            glm::vec4 clear_color { 0.0f, 0.0f, 0.0f, 1.0f };
        };

        struct meta
        {
        };

        struct sprite
        {
            // sptr<graphics::texture2d> texture;
            std::string texture_asset_guid;
        };

        component(flecs::world& world)
        {
            world.module<component>();

            // From flecs examples
            world.component<std::string>()
                .opaque(flecs::String)
                .serialize(
                    [](const flecs::serializer* s, const std::string* data)
                    {
                        const char* str = data->c_str();
                        return s->value(flecs::String, &str);
                    })
                .assign_string(
                    [](std::string* data, const char* value)
                    {
                        *data = value;
                    });
            world.component<glm::vec2>()
                .member("x", &glm::vec2::x)
                .member("y", &glm::vec2::y);
            world.component<glm::vec4>()
                .member("r", &glm::vec4::x)
                .member("g", &glm::vec4::y)
                .member("b", &glm::vec4::z)
                .member("a", &glm::vec4::w);

            world.component<position>().member<glm::vec2>("value");
            world.component<scale>().member<glm::vec2>("value");
            world.component<sprite>().member<std::string>("texture_asset_guid");

            world.component<scene_camera>().member<glm::vec4>("clear_color");
            world.component<meta>();

            flecs::system sprite_render_system
                = world
                      .system<const component::position,
                          const component::scale*,
                          const component::sprite>("SpriteRender")
                      .kind(flecs::OnUpdate)
                      .each(
                          [](const component::position& pos,
                              const component::scale* scale,
                              const component::sprite& sprite)
                          {
                              auto& database = app::get().get_asset_database();
                              auto sprite_asset
                                  = database.get_asset<asset::sprite_asset>(
                                      sprite.texture_asset_guid);
                              if (sprite_asset)
                              {
                                  glm::vec2 quad_scale { 1.0f, 1.0f };
                                  if (scale)
                                  {
                                      quad_scale = scale->value;
                                  }
                                  graphics::render2d::submit_quad(pos.value,
                                      quad_scale,
                                      sprite_asset->get_texture());
                              }
                          });

            flecs::system camera_update_view_system
                = world
                      .system<component::position,
                          const component::scene_camera>("UpdateViewMatrix")
                      .kind(flecs::PreUpdate)
                      .each(
                          [&](component::position& position,
                              const component::scene_camera& scene_camera)
                          {
                              // Clear current framebuffer attachments
                              graphics::render_command::clear_color(
                                  scene_camera.clear_color);
                              graphics::render_command::clear_depth();

                              graphics::render2d::set_view_matrix(
                                  glm::inverse(glm::translate(glm::mat4(1.0f),
                                      glm::vec3(position.value, 0.0f))));
                          });
            // auto query
            //     =
            //     world.query_builder().with("rotation").src("$test").build();
            // int test_index = query.find_var("test");

            // query.each(
            //     [&](flecs::iter& it, size_t index)
            //     {
            //         void* ptr =
            //         it.entity(index).ensure(it.get_var(test_index));

            //         flecs::world world = it.entity(index).world();
            //         flecs::cursor cursor
            //             = world.cursor(world.lookup("rotation"), ptr);
            //         cursor.push();
            //         cursor.set_float(20.0f);
            //         cursor.pop();
            //     });
        }
    };
}