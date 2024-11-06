#pragma once

#include "graphics/shader.hpp"
#include "glad/gl.h"

namespace narechi
{
    class opengl_shader : public graphics::shader
    {
    public:
        opengl_shader(const std::string& name, const char* vertex_src,
            const char* fragment_src);
        ~opengl_shader() override;
        
        void bind() override;
        void unbind() override;

        void set_int(const std::string& name, int value) override; 

    private:
        void compile(const char* vertex_src, const char* fragment_src);

        GLuint compile_shader(const GLenum type, const char* src);
    };
}