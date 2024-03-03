#pragma once

#include <core/window.hpp>

#include <GLFW/glfw3.h>

namespace narechi
{
    class win32window : public window
    {
    public:
        win32window(const window_properties& properties);

        virtual void* get_native_internal() const
        {
            return window;
        }

        virtual uint32_t get_width() const
        {
            return data.width;
        }

        virtual uint32_t get_height() const
        {
            return data.height;
        }

    private:
        void init(const window_properties& properties);

        struct window_data 
        {
            std::string title;

            uint32_t width, height;
        };

        window_data data;
        GLFWwindow* window;
    };
}