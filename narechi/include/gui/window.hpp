#pragma once

#include "core/core.hpp"

#include <string>

namespace narechi::gui
{
    struct window_properties
    {
        std::string name;
        uint32_t width, height;

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