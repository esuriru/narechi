#include "graphics/render_command.hpp"
#include "graphics/renderer_api.hpp"
#include "graphics/render2d.hpp"

namespace narechi::graphics
{
    uptr<renderer_api> render_command::renderer_api = renderer_api::create();

    void render_command::init()
    {
        renderer_api->init();
        render2d::init();
    }

    void render_command::cleanup()
    {
        renderer_api->cleanup();
    }

    void render_command::clear_color(const glm::vec4& color)
    {
        renderer_api->clear_color(color);
    }

    void render_command::draw_indexed(
        std::shared_ptr<graphics::vertex_array> vertex_array,
        uint32_t index_count)
    {
        renderer_api->draw_indexed(vertex_array, index_count);
    }

    void render_command::set_viewport(const uint32_t x, const uint32_t y,
        const uint32_t width, const uint32_t height)
    {
        renderer_api->set_viewport(x, y, width, height);
    }
}