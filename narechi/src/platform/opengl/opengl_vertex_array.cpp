#include "platform/opengl/opengl_vertex_array.hpp"

#include "glad/gl.h"

namespace narechi
{
    opengl_vertex_array::opengl_vertex_array()
    {
        glCreateVertexArrays(1, &id);
    }

    opengl_vertex_array::~opengl_vertex_array()
    {
        glDeleteVertexArrays(1, &id);
    }

    void opengl_vertex_array::bind()
    {
        glBindVertexArray(id);
    }

    void opengl_vertex_array::unbind()
    {
        glBindVertexArray(0);
    }
}
