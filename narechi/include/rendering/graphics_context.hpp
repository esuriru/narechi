#pragma once

#include "core/core.hpp"

namespace narechi
{
    class graphics_context
    {
    public:
        virtual void init() = 0;
        virtual void swap_buffers() = 0;
    };
}