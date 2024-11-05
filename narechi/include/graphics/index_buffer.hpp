#pragma once

#include "core/core.hpp"
#include "graphics/handle.hpp"

namespace narechi::graphics
{
    class index_buffer : public handle
    {
    public:
        virtual ~index_buffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        static sptr<index_buffer> create(
            const uint32_t* indices, const uint32_t count);
    };
}