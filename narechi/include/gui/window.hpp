#pragma once

#include "core/core.hpp"

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

        static uptr<window> create_window(const window_properties& props);

    protected:
        window(const window_properties& props);

        std::string name;
    };
}