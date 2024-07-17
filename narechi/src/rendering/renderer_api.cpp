#include "rendering/renderer_api.hpp"

#include "core/logger.hpp"

#include <platform/vulkan/vulkan_renderer_api.hpp>
#include <platform/vulkan/opengl_renderer_api.hpp>

namespace narechi
{
    renderer_api::api renderer_api::api_type = renderer_api::api::vulkan;

    uptr<renderer_api> renderer_api::create()
    {
        switch (api_type)
        {
        case renderer_api::api::none:
            NRC_CORE_FATAL("Renderer API cannot be none!");
            break;
        case renderer_api::api::opengl:
            return make_uptr<opengl_renderer_api>();
        case renderer_api::api::vulkan:
            return make_uptr<vulkan_renderer_api>();
        }

        return nullptr;
    }
}