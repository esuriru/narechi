#include "panels/scene_view_panel.hpp"
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
        });

        window->add_element(scene_image);
    }

    void scene_view_panel::render()
    {
        auto color_attachment = scene_framebuffer->get_color_attachment();
        scene_image->set_texture_gfx_ctx_id(color_attachment->get_id());
        scene_image->set_width(color_attachment->get_width());
        scene_image->set_height(color_attachment->get_height());

        window->render();
    }
}