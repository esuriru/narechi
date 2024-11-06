#pragma once

#include "graphics/framebuffer.hpp"

namespace narechi
{
    class opengl_framebuffer : public graphics::framebuffer
    {
    public:
        opengl_framebuffer(const graphics::framebuffer_specification& spec);
    };
}