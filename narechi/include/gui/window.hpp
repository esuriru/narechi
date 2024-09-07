#pragma once

#include "core/core.hpp"
#include "gui/element.hpp"

#include <string>

namespace narechi::gui
{
    struct window_properties
    {
        std::string name;
        uint32_t width = 0, height = 0;

        uint32_t start_position_x = 0, start_position_y = 0;

        static bool verify(const window_properties& props);
    };

    class NRC_API window
    {
    public:
        virtual void render() = 0;

        static uptr<window> create(const window_properties& props);
        virtual void add_element(uptr<element>&& element) = 0;

        void set_width_height(uint32_t width, uint32_t height);

        uint32_t get_width()
        {
            return width;
        }

        uint32_t get_height()
        {
            return height;
        }

    protected:
        window(const window_properties& props);

        virtual void set_width_height_impl(uint32_t width, uint32_t height) = 0;

        std::string name;
        uint32_t width, height;
    };
}