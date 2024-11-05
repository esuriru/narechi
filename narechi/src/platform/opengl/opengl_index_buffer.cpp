#include "platform/opengl/opengl_index_buffer.hpp"

#include "glad/gl.h"

namespace narechi
{
    opengl_index_buffer::opengl_index_buffer(
        const uint32_t* indices, const uint32_t count)
    {
        glCreateBuffers(1, &id);
        glNamedBufferData(id,
            static_cast<GLint>(count * sizeof(uint32_t)),
            indices,
            GL_STATIC_DRAW);
    }

    opengl_index_buffer::~opengl_index_buffer()
    {
        glDeleteBuffers(1, &id);
    }

    void opengl_index_buffer::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void opengl_index_buffer::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
