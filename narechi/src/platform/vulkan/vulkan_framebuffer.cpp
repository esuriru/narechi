#include "platform/vulkan/vulkan_framebuffer.hpp"
#include "rendering/framebuffer.hpp"

namespace narechi
{
    vulkan_framebuffer::vulkan_framebuffer(
        const framebuffer_specification& specification)
        : specification(specification)
    {
    }

    void vulkan_framebuffer::bind() {}

    void vulkan_framebuffer::unbind() {}

    void vulkan_framebuffer::resize(uint32_t width, uint32_t height) {}

    const framebuffer_specification& vulkan_framebuffer::get_specification()
        const
    {
    }
}