#include "platform/opengl/opengl_renderer_api.hpp"

#include "glad/gl.h"
#include "glm/gtc/type_ptr.hpp"

namespace narechi
{
    void opengl_renderer_api::init()
    {
        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            GL_ONE,
            GL_ONE_MINUS_SRC_ALPHA);

        // Enable depth
        // glEnable(GL_DEPTH_TEST);
    }

    void opengl_renderer_api::clear_color(const glm::vec4& color)
    {
        // glClearColor(color.r, color.g, color.b, color.a);
        // glClear(GL_COLOR_BUFFER_BIT);
        // 0 since there isn't any framebuffers with more than 1 color
        // attachment
        glClearBufferfv(GL_COLOR, 0, glm::value_ptr(color));
    }

    void opengl_renderer_api::clear_depth(const float depth)
    {
        // glClearDepth(depth);
        // glClear(GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_DEPTH, 0, &depth);
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

    void opengl_renderer_api::set_viewport(const uint32_t x, const uint32_t y,
        const uint32_t width, const uint32_t height)
    {
        glViewport(x, y, width, height);
    }
}
