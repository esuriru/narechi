#pragma once

#include <core/events/event.hpp>
#include <format>

namespace narechi
{
    class window_resize_event : public event
    {
        NRC_EVENT_TYPE(window_resize)
        NRC_EVENT_CATEGORY(application_event_category)

    public:
        window_resize_event(uint32_t width, uint32_t height)
            : width(width), height(height)
        {
        }

        uint32_t get_width()
        {
            return width;
        }

        uint32_t get_height()
        {
            return height;
        }

        std::string to_string() const override
        {
            return std::format("WindowResizeEvent: {}, {}", width, height);
        }

    private:
        uint32_t width, height;
    };

    class window_close_event : public event
    {
        NRC_EVENT_TYPE(window_close)
        NRC_EVENT_CATEGORY(application_event_category)

    public:
        window_close_event() = default;
    };
}