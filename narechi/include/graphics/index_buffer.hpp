#pragma once

#include "core/core.hpp"
#include "graphics/handle.hpp"

namespace narechi::graphics
{
    class index_buffer : public handle
    {
    public:
        index_buffer(const uint32_t count);
        virtual ~index_buffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual uint32_t get_count() const;

        static sptr<index_buffer> create(
            const uint32_t* indices, const uint32_t count);
    
    protected:
        uint32_t count;
    };
}