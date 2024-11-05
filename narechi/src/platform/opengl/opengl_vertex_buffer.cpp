#include "platform/opengl/opengl_vertex_buffer.hpp"

#include "glad/gl.h"

namespace narechi
{
    opengl_vertex_buffer::opengl_vertex_buffer(
        const float* vertices, const uint32_t size)
    {
        glCreateBuffers(1, &id);
        glNamedBufferData(
            id, static_cast<GLint>(size), vertices, GL_STATIC_DRAW);
    }

    opengl_vertex_buffer::~opengl_vertex_buffer()
    {
        glDeleteBuffers(1, &id);
    }

    void narechi::opengl_vertex_buffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void narechi::opengl_vertex_buffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}