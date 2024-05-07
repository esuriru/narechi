#include "rendering/framebuffer.hpp"
#include "rendering/renderer_api.hpp"
#include "core/core.hpp"
#include "core/logger.hpp"
#include "platform/vulkan/vulkan_framebuffer.hpp"

namespace narechi
{
    sptr<framebuffer> framebuffer::create(const framebuffer_specification& spec)
    {
        switch (renderer_api::get_api())
        {
        case renderer_api::api::vulkan:
            return make_sptr<vulkan_framebuffer>(spec);
        default:
            break;
        }

        NRC_CORE_ERROR("No framebuffer available for selected Renderer API");
        return nullptr;
    }
}
