#pragma once

#include "core/core.hpp"
#include "graphics/renderer_api.hpp"

namespace narechi::graphics
{
    class render_command final
    {
    public:
        static void init()
        {
            renderer_api->init();
        }

        static void cleanup()
        {
            renderer_api->cleanup();
        }

        // TODO -  Color class
        static void clear_color(const glm::vec4& color)
        {
            renderer_api->clear_color(color);
        }

        static void draw()
        {
        }

    private:
        static uptr<renderer_api> renderer_api;
    };

}