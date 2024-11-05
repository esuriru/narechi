#pragma once

#include "core/core.hpp"
#include "graphics/renderer_api.hpp"
#include "graphics/vertex_array.hpp"

namespace narechi::graphics
{
    class render_command final
    {
    public:
        static void init();
        static void cleanup();

        // TODO -  Color class
        static void clear_color(const glm::vec4& color);

        static void draw_indexed(
            std::shared_ptr<graphics::vertex_array> vertex_array,
            uint32_t index_count = 0);

    private:
        static uptr<renderer_api> renderer_api;
    };

}