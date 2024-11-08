#pragma once

#include "core/core.hpp"
#include "graphics/handle.hpp"
#include "graphics/texture.hpp"

#include "glm/glm.hpp"

#include <cstdint>

namespace narechi::graphics
{
    struct NRC_API framebuffer_specification
    {
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t samples = 1;

        bool swap_chain_target = false;
    };

    class NRC_API framebuffer : public handle
    {
    public:
        virtual ~framebuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;
        virtual const framebuffer_specification& get_specification() const;

        virtual void clear_color(const glm::vec4& color) = 0;
        virtual void clear_depth(const float depth = 1.0f) = 0;

        virtual sptr<texture> get_color_attachment() = 0;
        virtual sptr<texture> get_depth_attachment() = 0;

        static sptr<framebuffer> create(const framebuffer_specification& spec);

    protected:
        framebuffer(const framebuffer_specification& spec);

        framebuffer_specification spec;
    };
}