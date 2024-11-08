#include "panels/scene_view_panel.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "graphics/render2d.hpp"
#include "gui/image_element.hpp"

namespace narechi::editor
{
    scene_view_panel::scene_view_panel(sptr<graphics::framebuffer> framebuffer)
        : editor_panel("Scene View")
        , scene_framebuffer(framebuffer)
        , window(gui::window::create(
              { .name = "Scene", .width = 600, .height = 800 }))
    {
        scene_image = gui::image_element::create({
            .texture_gfx_ctx_id = framebuffer->get_color_attachment()->get_id(),
            .flip_vertically = true,
        });

        window->add_element(scene_image);
    }

    void scene_view_panel::render()
    {
        auto color_attachment = scene_framebuffer->get_color_attachment();
        scene_image->set_texture_gfx_ctx_id(color_attachment->get_id());
        const auto& spec = scene_framebuffer->get_specification();
        static float previous_width = spec.width;
        static float previous_height = spec.height;

        window->render(
            [this]()
            {
                float width = window->get_width();
                float height = window->get_height();

                if (previous_width != width || previous_height != height)
                {
                    scene_framebuffer->resize(width, height);
                    previous_width = width;
                    previous_height = height;

                    invalidate_proj_matrix();
                }

                scene_image->set_width(width);
                scene_image->set_height(height);

                scene_image->render();
            });
    }

    void scene_view_panel::invalidate_proj_matrix()
    {
        float scale = 0.05f;
        float width
            = (static_cast<float>(scene_framebuffer->get_specification().width)
                  * scale)
            * 0.5f;
        float height
            = (static_cast<float>(scene_framebuffer->get_specification().height)
                  * scale)
            * 0.5f;
        graphics::render2d::set_proj_matrix(
            glm::ortho(-width, width, -height, height, -10.0f, 10.0f));
    }
}