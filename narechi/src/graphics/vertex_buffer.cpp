#include "graphics/vertex_buffer.hpp"
#include "graphics/renderer_api.hpp"

#ifdef NRC_RENDERER_API_OPENGL
    #include "platform/opengl/opengl_vertex_buffer.hpp"
#endif

namespace narechi::graphics
{
    sptr<vertex_buffer> vertex_buffer::create(
        const float* vertices, const uint32_t size)
    {
        switch (renderer_api::get_api())
        {
        case renderer_api::api::opengl:
#ifdef NRC_RENDERER_API_OPENGL
            return make_sptr<opengl_vertex_buffer>(vertices, size);
#else
            NRC_CORE_FATAL("OpenGL is not compiled, but selected");
#endif
        default:
            break;
        }

        NRC_CORE_ERROR("No vertex array available for selected Renderer API");
        return nullptr;
    }

    const vertex_buffer::buffer_layout& vertex_buffer::get_layout() const
    {
        return this->layout;
    }
}