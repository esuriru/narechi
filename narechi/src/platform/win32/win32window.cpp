#include "platform/win32/win32window.hpp"

#include <core/logger.hpp>
#include <core/events/app_event.hpp>

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

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        if (window = glfwCreateWindow(properties.width,
                properties.height,
                properties.title.c_str(),
                nullptr,
                nullptr))
        {
            NRC_CORE_DEBUG("GLFW Window created");
        }

        glfwSetWindowUserPointer(window, &data);

        glfwSetWindowSizeCallback(window,
            [](GLFWwindow* window, int width, int height)
            {
                window_data& data
                    = *(window_data*)glfwGetWindowUserPointer(window);

                data.width = width;
                data.height = height;

                window_resize_event event(width, height);
                data.event_callback(event);
            });

        glfwSetWindowCloseCallback(window,
            [](GLFWwindow* window)
            {
                window_data& data
                    = *(window_data*)glfwGetWindowUserPointer(window);

                window_close_event event;
                data.event_callback(event);
            });
    }

    void win32window::cleanup()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}