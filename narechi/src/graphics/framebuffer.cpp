#include "graphics/framebuffer.hpp"
#include "graphics/renderer_api.hpp"

#include "core/core.hpp"
#include "core/logger.hpp"

#if defined(NRC_RENDERER_API_VULKAN)
    #include "platform/vulkan/vulkan_framebuffer.hpp"
#elif defined(NRC_RENDERER_API_OPENGL)
    #include "platform/opengl/opengl_framebuffer.hpp"
#else
    #error "Unsupported renderer API"
#endif

namespace narechi::graphics
{
    const framebuffer_specification& framebuffer::get_specification() const
    {
        return spec;
    }

    sptr<framebuffer> framebuffer::create(const framebuffer_specification& spec)
    {
        switch (renderer_api::get_api())
        {
        case renderer_api::api::vulkan:
#ifdef NRC_RENDERER_API_VULKAN
            return make_sptr<vulkan_framebuffer>(spec);
#else
            NRC_CORE_FATAL("Vulkan is not compiled, but selected");
#endif
        case renderer_api::api::opengl:
#ifdef NRC_RENDERER_API_OPENGL
            return make_sptr<opengl_framebuffer>(spec);
#else
            NRC_CORE_FATAL("OpenGL is not compiled, but selected");
#endif
        default:
            break;
        }

        NRC_CORE_ERROR("No framebuffer available for selected Renderer API");
        return nullptr;
    }

    framebuffer::framebuffer(const framebuffer_specification& spec)
        : spec(spec)
    {
    }
}
