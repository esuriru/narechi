#pragma once

#include "core/core.hpp"
#include "graphics/handle.hpp"

namespace narechi::graphics
{
    class NRC_API texture : public handle
    {
    public:
        virtual ~texture() = default;
        virtual uint32_t get_width() const = 0;
        virtual uint32_t get_height() const = 0;
    };
}
