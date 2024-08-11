#include "platform/opengl/opengl_context.hpp"

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "core/assert.hpp"

namespace narechi
{
    opengl_context::opengl_context(GLFWwindow* window)
        : graphics_context(), window(window)
    {
        NRC_ASSERT(window,
            "OpenGL Context could not be created because "
            "window is null");
    }

    opengl_context::~opengl_context()
    {
        
    }

    void opengl_context::init()
    {
        NRC_ASSERT(window,
            "OpenGL Context could not be initialized because "
            "window is null");
        glfwMakeContextCurrent(window);

        NRC_VERIFY(gladLoadGL(glfwGetProcAddress), "GLAD could not initialize");
    }

    void opengl_context::swap_buffers()
    {
        glfwSwapBuffers(window);
    }
}