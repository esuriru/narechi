#pragma once

#include "core/core.hpp"
#include "graphics/renderer_api.hpp"
#include "graphics/vertex_array.hpp"

namespace narechi::graphics
{
    class NRC_API render_command final
    {
    public:
        static void init();
        static void cleanup();

        // TODO -  Color class
        static void clear_color(const glm::vec4& color);

        static void draw_indexed(
            std::shared_ptr<graphics::vertex_array> vertex_array,
            uint32_t index_count = 0);
        static void set_viewport(const uint32_t x, const uint32_t y,
            const uint32_t width, const uint32_t height);

    private:
        static uptr<renderer_api> renderer_api;
    };

}