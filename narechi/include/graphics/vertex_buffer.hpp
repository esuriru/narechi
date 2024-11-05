#pragma once

#include "core/core.hpp"

#include "graphics/handle.hpp"
#include "graphics/buffer_element.hpp"

#include <vector>

namespace narechi::graphics
{
    class vertex_buffer : public handle
    {
    public:
        struct buffer_layout
        {
            std::vector<graphics::buffer_element> elements;
        };

        virtual ~vertex_buffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual const buffer_layout& get_layout() const;

        static sptr<vertex_buffer> create(
            const float* vertices, const uint32_t size);

    private:
        buffer_layout layout;
    };
}