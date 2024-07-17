#pragma once

#include "core/core.hpp"
#include "rendering/renderer_api.hpp"
#include "platform/vulkan/vulkan_renderer_api.hpp"

namespace narechi
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

        static void draw()
        {
            static_cast<vulkan_renderer_api*>(renderer_api.get())->draw_frame();
        }

    private:
        static uptr<renderer_api> renderer_api;
    };

}