#include "platform/opengl/opengl_renderer_api.hpp"

#include "glad/gl.h"

namespace narechi
{
    void opengl_renderer_api::clear_color(const glm::vec4& color)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(color.r, color.g, color.b, color.a);
    }
}
