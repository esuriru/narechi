#pragma once

#include "core/core.hpp"

namespace narechi::graphics
{
    class vertex_array
    {
    public:
        virtual ~vertex_array() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        static sptr<vertex_array> create();
    };
}