#include "rendering/renderer_api.hpp"

#include "core/assert.hpp"
#include "core/logger.hpp"

#if defined(NRC_RENDERER_API_VULKAN)
    #include "platform/vulkan/vulkan_renderer_api.hpp"
#elif defined(NRC_RENDERER_API_OPENGL)
    #include "platform/opengl/opengl_renderer_api.hpp"
#else
    #error "Unsupported renderer API"
#endif

namespace narechi
{
    // TODO - The renderer API classes should just be forward declared

#if defined(NRC_RENDERER_API_VULKAN)
    renderer_api::api renderer_api::api_type = renderer_api::api::vulkan;
#elif defined(NRC_RENDERER_API_OPENGL)
    renderer_api::api renderer_api::api_type = renderer_api::api::opengl;
#else
    #error "Unsupported renderer API"
#endif

    uptr<renderer_api> renderer_api::create()
    {
        switch (api_type)
        {
        case renderer_api::api::none:
            NRC_CORE_FATAL("Renderer API cannot be none");
            break;
        case renderer_api::api::opengl:
#ifdef NRC_RENDERER_API_OPENGL
            return make_uptr<opengl_renderer_api>();
#else
            NRC_CORE_FATAL("OpenGL is not compiled, but selected");
#endif
        case renderer_api::api::vulkan:
#ifdef NRC_RENDERER_API_VULKAN
            return make_uptr<vulkan_renderer_api>();
#else
            NRC_CORE_FATAL("Vulkan is not compiled, but selected");
#endif
        }

        return nullptr;
    }
}