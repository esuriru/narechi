#pragma once

#include "graphics/shader.hpp"

namespace narechi
{
    class opengl_shader : public graphics::shader
    {
    public:
        opengl_shader(const std::string& name, const char* vertex_src,
            const char* fragment_src);
     
    };
}