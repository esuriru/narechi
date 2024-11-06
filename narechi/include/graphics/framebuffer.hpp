#pragma once

#include "core/core.hpp"
#include "graphics/handle.hpp"

#include <cstdint>

namespace narechi::graphics
{
    struct framebuffer_specification
    {
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t samples = 1;

        bool swap_chain_target = false;
    };

    class framebuffer : public handle
    {
    public:
        virtual ~framebuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;
        virtual const framebuffer_specification& get_specification() const = 0;

        static sptr<framebuffer> create(const framebuffer_specification& spec);
    };
}