#include "platform/opengl/opengl_shader.hpp"

#include "core/assert.hpp"

namespace narechi
{
    opengl_shader::opengl_shader(const std::string& name,
        const char* vertex_src, const char* fragment_src)
        : shader(name)
    {
        NRC_ASSERT(vertex_src, "Vertex shader source is empty");
        NRC_ASSERT(fragment_src, "Fragment shader source is empty");

        compile(vertex_src, fragment_src);
    }

    opengl_shader::~opengl_shader()
    {
        glDeleteProgram(id);
    }

    void opengl_shader::bind()
    {
        glUseProgram(id);
    }

    void opengl_shader::unbind()
    {
        glUseProgram(0);
    }

    void opengl_shader::set_int(const std::string& name, int value)
    {
        const auto& location = glGetUniformLocation(id, name.c_str());
        glUniform1i(location, value);
    }

    void opengl_shader::compile(
        const char* vertex_src, const char* fragment_src)
    {
        GLuint program_handle = glCreateProgram();
        // Compile vertex shader
        GLuint vertex_shader_handle
            = compile_shader(GL_VERTEX_SHADER, vertex_src);
        if (vertex_shader_handle == 0)
        {
            NRC_CORE_ERROR("Failed to compile vertex shader");

            glDeleteProgram(program_handle);
            return;
        }

        GLuint fragment_shader_handle
            = compile_shader(GL_FRAGMENT_SHADER, fragment_src);
        if (fragment_shader_handle == 0)
        {
            NRC_CORE_ERROR("Failed to compile fragment shader");

            glDeleteShader(vertex_shader_handle);
            glDeleteProgram(program_handle);
            return;
        }

        glAttachShader(program_handle, vertex_shader_handle);
        glAttachShader(program_handle, fragment_shader_handle);

        glLinkProgram(program_handle);

        // Query link status
        GLint is_linked = GL_FALSE;
        glGetProgramiv(program_handle, GL_LINK_STATUS, &is_linked);

        if (is_linked == GL_FALSE)
        {
            GLint max_length = 0;
            glGetProgramiv(program_handle, GL_INFO_LOG_LENGTH, &max_length);

            std::string program_log;
            program_log.resize(max_length);
            glGetProgramInfoLog(
                program_handle, max_length, &max_length, program_log.data());

            NRC_CORE_ERROR(
                "Failed to link opengl program. Log: " + program_log);

            // Cleanup
            glDeleteShader(vertex_shader_handle);
            glDeleteShader(fragment_shader_handle);
            glDeleteProgram(program_handle);
        }

        glDetachShader(program_handle, vertex_shader_handle);
        glDetachShader(program_handle, fragment_shader_handle);

        id = program_handle;
    }

    GLuint opengl_shader::compile_shader(const GLenum type, const char* src)
    {
        GLuint shader_handle = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shader_handle, 1, &src, nullptr);

        // Query compilation status
        GLint is_compiled = GL_FALSE;
        glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &is_compiled);

        if (is_compiled == GL_FALSE)
        {
            GLint max_length = 0;
            glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &max_length);

            std::string shader_log;
            shader_log.resize(max_length);
            glGetShaderInfoLog(
                shader_handle, max_length, &max_length, shader_log.data());

            NRC_CORE_ERROR(
                "Failed to compile opengl shader. Log: " + shader_log);

            glDeleteShader(shader_handle);

            return 0;
        }

        return shader_handle;
    }
}