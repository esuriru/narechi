#include "graphics/vertex_array.hpp"

#include "core/logger.hpp"

#ifdef NRC_RENDERER_API_OPENGL
// #include "platform/opengl/opengl_vertex_array.hpp"
#endif

namespace narechi::graphics
{
    sptr<vertex_array> vertex_array::create()
    {
    case renderer_api::api::opengl:
#ifdef NRC_RENDERER_API_OPENGL
        return make_sptr<opengl_vertex_array>();
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