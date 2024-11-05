#pragma once

#include "core/core.hpp"

namespace narechi::graphics
{
    class index_buffer
    {
    public:
        virtual ~index_buffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        static sptr<index_buffer> create(
            const uint32_t* indices, const uint32_t count);
    };
}