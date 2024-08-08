#pragma once

#include "rendering/graphics_context.hpp"

struct GLFWwindow;

namespace narechi
{
    class opengl_context : public graphics_context
    {
    public:
        opengl_context(GLFWwindow* window);

        void init() override;
        void swap_buffers() override;

    private:
        GLFWwindow* window;
    };
}