#include "graphics/shader.hpp"
#include "graphics/renderer_api.hpp"

#ifdef NRC_RENDERER_API_OPENGL
    #include "platform/opengl/opengl_shader.hpp"
#endif

namespace narechi::graphics
{
    shader::shader(const std::string& name)
        : name(name)
    {
    }

    const std::string& shader::get_name()
    {
        return name;
    }

    sptr<shader> shader::create(const std::string& name, const char* vertex_src,
        const char* fragment_src)
    {
        switch (renderer_api::get_api())
        {
        case renderer_api::api::opengl:
#ifdef NRC_RENDERER_API_OPENGL
            return make_sptr<opengl_shader>(name, vertex_src, fragment_src);
#else
            NRC_CORE_FATAL("OpenGL is not compiled, but selected");
#endif
        default:
            break;
        }

        NRC_CORE_ERROR("No shader available for selected Renderer API");
        return nullptr;
    }
}