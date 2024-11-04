#pragma once

#include "core/core.hpp"

namespace narechi::graphics
{
    class vertex_buffer
    {
    public:
        virtual ~vertex_buffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        static sptr<vertex_buffer> create(
            const float* vertices, const uint32_t size);
    };
}