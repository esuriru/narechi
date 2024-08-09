#include "platform/win32/win32window.hpp"

#include "platform/opengl/opengl_context.hpp"

#include "GLFW/glfw3.h"

#include "core/logger.hpp"
#include "core/assert.hpp"
#include "core/events/app_event.hpp"

namespace narechi
{
    win32window::win32window(const window_properties& properties)
    {
        // TODO - A possible profiling function here

        init(properties);
    }

    win32window::~win32window()
    {
        cleanup();
    }

    void win32window::update()
    {
        glfwPollEvents();
    }

    void win32window::init(const window_properties& properties)
    {
        data.title = properties.title;
        data.width = properties.width;
        data.height = properties.height;

        NRC_VERIFY(glfwInit() == GLFW_TRUE, "GLFW could not initialize");
        glfwSetErrorCallback(
            [](int error, const char* desc)
            {
                NRC_CORE_ERROR("GLFW error: (", error, "): {", desc, "}");
            });

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        // TODO - Versions
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        NRC_VERIFY((window = glfwCreateWindow(properties.width,
                        properties.height,
                        properties.title.c_str(),
                        nullptr,
                        nullptr)),
            "Could not create GLFW window");
        NRC_CORE_DEBUG("GLFW Window created");

        graphics_context = make_uptr<opengl_context>(window);
        graphics_context->init();

        glfwSetWindowUserPointer(window, &data);

        glfwSetWindowSizeCallback(window,
            [](GLFWwindow* window, int width, int height)
            {
                window_data* data = reinterpret_cast<window_data*>(
                    glfwGetWindowUserPointer(window));

                data->width = width;
                data->height = height;

                window_resize_event event(width, height);
                data->event_callback(event);
            });

        glfwSetWindowCloseCallback(window,
            [](GLFWwindow* window)
            {
                window_data* data = reinterpret_cast<window_data*>(
                    glfwGetWindowUserPointer(window));

                window_close_event event;
                data->event_callback(event);
            });
    }

    void win32window::cleanup()
    {
        graphics_context.reset();

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}