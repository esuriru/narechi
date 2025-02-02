#pragma once

#include "graphics/graphics_context.hpp"

struct GLFWwindow;

namespace narechi
{
    class opengl_context : public graphics::graphics_context
    {
    public:
        opengl_context(GLFWwindow* window);
        ~opengl_context();

        void init() override;
        void swap_buffers() override;

    private:
        GLFWwindow* window;
    };
}