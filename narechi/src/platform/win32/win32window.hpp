#pragma once

#include <core/window.hpp>
#include <core/events/event.hpp>

#include <GLFW/glfw3.h>

namespace narechi
{
    class win32window : public window
    {
    public:
        win32window(const window_properties& properties);

        virtual void update() override;

        virtual void set_event_callback(event_callback_fn callback) override
        {
            data.event_callback = callback;
        }

        virtual void* get_native_internal() const override
        {
            return window;
        }

        virtual uint32_t get_width() const override
        {
            return data.width;
        }

        virtual uint32_t get_height() const override
        {
            return data.height;
        }

    private:
        void init(const window_properties& properties);

        struct window_data 
        {
            std::string title;

            uint32_t width, height;
            event_callback_fn event_callback;
        };

        window_data data;
        GLFWwindow* window;
    };
}