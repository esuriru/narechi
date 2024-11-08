#include "platform/opengl/opengl_renderer_api.hpp"

#include "glad/gl.h"

namespace narechi
{
    void opengl_renderer_api::init()
    {
        // Enable depth
        glEnable(GL_DEPTH_TEST);
    }

    void opengl_renderer_api::clear_color(const glm::vec4& color)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void opengl_renderer_api::draw_indexed(
        std::shared_ptr<graphics::vertex_array> vertex_array,
        uint32_t index_count)
    {
        vertex_array->bind();
        uint32_t count = index_count == 0 ?
            vertex_array->get_index_buffer()->get_count() :
            index_count;
        glDrawElements(
            GL_TRIANGLES, static_cast<GLint>(count), GL_UNSIGNED_INT, nullptr);
    }
}
