#pragma once

#include "core/core.hpp"

namespace narechi
{
    class app;

    class graphics_context
    {
    public:
        virtual ~graphics_context();

        static uptr<graphics_context> create(app* app);

        virtual void init() = 0;
        virtual void swap_buffers() = 0;
    };
}