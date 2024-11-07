#include "platform/opengl/opengl_vertex_array.hpp"

#include "glad/gl.h"
#include "graphics/shader_data_type.hpp"

namespace
{
    using narechi::graphics::shader_data_type;

    static GLenum shader_data_type_to_opengl_data_type(
        const shader_data_type type)
    {
        switch (type)
        {
        case shader_data_type::float1:
        case shader_data_type::float2:
        case shader_data_type::float3:
        case shader_data_type::float4:
        case shader_data_type::mat3:
        case shader_data_type::mat4:
            return GL_FLOAT;
        case shader_data_type::int1:
        case shader_data_type::int2:
        case shader_data_type::int3:
        case shader_data_type::int4:
            return GL_INT;
        case shader_data_type::bool1:
            return GL_BOOL;
        case shader_data_type::none:
            break;
        }

        NRC_CORE_FATAL("shader data type not handled, shader data type: ",
            shader_data_type_to_string(type));
        return 0;
    }
}

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

    void opengl_vertex_array::add_vertex_buffer(
        sptr<graphics::vertex_buffer> vertex_buffer)
    {
        uint32_t attrib_index = 0;
        uint32_t binding_index = vertex_buffers.size();
        const auto& layout = vertex_buffer->get_layout();

        glVertexArrayVertexBuffer(
            id, binding_index, vertex_buffer->get_id(), 0, layout.get_stride());

        for (const auto& element : layout.get_elements())
        {
            glEnableVertexArrayAttrib(id, attrib_index);
            glVertexArrayAttribFormat(id,
                attrib_index,
                static_cast<GLint>(element.get_component_count()),
                shader_data_type_to_opengl_data_type(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                static_cast<GLuint>(element.offset));
            glVertexArrayAttribBinding(id, attrib_index, binding_index);
            ++attrib_index;
        }

        vertex_buffers.push_back(vertex_buffer);
    }

    void opengl_vertex_array::set_index_buffer(
        sptr<graphics::index_buffer> index_buffer)
    {
        glVertexArrayElementBuffer(id, index_buffer->get_id());
        this->index_buffer = index_buffer;
    }

    sptr<graphics::index_buffer> opengl_vertex_array::get_index_buffer() const
    {
        return index_buffer;
    }

    const std::vector<sptr<graphics::vertex_buffer>>&
    opengl_vertex_array::get_vertex_buffers() const
    {
        return vertex_buffers;
    }
}
