#pragma once

#include "core/core.hpp"

NRC_FORWARD_DECL_CLASS(narechi, app)

namespace narechi::graphics
{
    class graphics_context
    {
    public:
        virtual ~graphics_context();

        static uptr<graphics_context> create(app* app);

        virtual void init() = 0;
        virtual void swap_buffers() = 0;
    };
}