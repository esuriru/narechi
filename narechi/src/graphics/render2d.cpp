#include "graphics/render2d.hpp"

#include "core/core.hpp"
#include "graphics/shader.hpp"
#include "asset/embed.hpp"

NRC_DECL_EMBED_STD_STRING(texture_v);
NRC_DECL_EMBED_STD_STRING(texture_f);

namespace
{
    using narechi::sptr;
    sptr<narechi::graphics::shader> texture_shader;
}

namespace narechi::graphics::render2d
{
    void init()
    {
        using namespace embed;

        texture_shader
            = shader::create("texture", texture_v.c_str(), texture_f.c_str());
    }
}