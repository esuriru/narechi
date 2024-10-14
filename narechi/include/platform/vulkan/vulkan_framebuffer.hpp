#pragma once

#include "rendering/framebuffer.hpp"

namespace narechi
{
    class vulkan_framebuffer : public framebuffer
    {
    public:
        vulkan_framebuffer(const framebuffer_specification& specification);

        void bind() override;
        void unbind() override;

        void resize(uint32_t width, uint32_t height) override;
        const framebuffer_specification& get_specification() const override;

    private:
        framebuffer_specification specification;
    };
}