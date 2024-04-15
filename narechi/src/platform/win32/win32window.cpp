#include "win32window.hpp"

#include <core/logger.hpp>

namespace narechi
{
    win32window::win32window(const window_properties& properties)
    {
        // TODO - A possible profiling function here

        init(properties);
    }

    void win32window::init(const window_properties& properties)
    {
        data.title = properties.title;
        data.width = properties.width;
        data.height = properties.height;

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        if (window = glfwCreateWindow(properties.width, 
            properties.height, properties.title.c_str(), 
            nullptr, nullptr))
        {
            NRC_CORE_DEBUG("GLFW Window created");
        }
    }
}