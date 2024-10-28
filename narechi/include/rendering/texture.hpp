#pragma once

#include "core/core.hpp"

namespace narechi::rendering
{
    class NRC_API texture
    {
    public:
        virtual ~texture() = default;
        virtual uint32_t get_width() const = 0;
        virtual uint32_t get_height() const = 0;

        virtual uint32_t get_gfx_ctx_id() const = 0;
    };
}
