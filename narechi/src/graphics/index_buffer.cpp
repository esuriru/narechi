#include "graphics/index_buffer.hpp"

#include "core/logger.hpp"
#include "graphics/renderer_api.hpp"

#ifdef NRC_RENDERER_API_OPENGL
    #include "platform/opengl/opengl_index_buffer.hpp"
#endif

namespace narechi::graphics
{
    sptr<index_buffer> index_buffer::create(
        const uint32_t* indices, const uint32_t count)
    {
        switch (renderer_api::get_api())
        {
        case renderer_api::api::opengl:
#ifdef NRC_RENDERER_API_OPENGL
            return make_sptr<opengl_index_buffer>(indices, count);
#else
            NRC_CORE_FATAL("OpenGL is not compiled, but selected");
#endif
        default:
            break;
        }

        NRC_CORE_ERROR("No vertex array available for selected Renderer API");
        return nullptr;
    }
}