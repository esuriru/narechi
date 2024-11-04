#include "graphics/framebuffer.hpp"
#include "graphics/renderer_api.hpp"

#include "core/core.hpp"
#include "core/logger.hpp"

#ifdef NRC_RENDERER_API_VULKAN
    #include "platform/vulkan/vulkan_framebuffer.hpp"
#endif

namespace narechi::graphics
{
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
        default:
            break;
        }

        NRC_CORE_ERROR("No framebuffer available for selected Renderer API");
        return nullptr;
    }
}
