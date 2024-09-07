#include "gui/window.hpp"
#include "imgui/imgui_window.hpp"
#include "core/assert.hpp"

namespace narechi::gui
{
    bool window_properties::verify(const window_properties& props)
    {
        NRC_VERIFY(!props.name.empty(), "The GUI window name cannot be empty");
        NRC_VERIFY(props.name[0] != '\0',
            "The GUI window's name cannot have a "
            "whitespace as the first character");

        return true;
    }

    uptr<window> window::create(const window_properties& props)
    {
        NRC_VERIFY(window_properties::verify(props),
            "GUI window properties argument error");

        // There is only IMGUI for now
        return make_uptr<imgui_window>(props);
    }

    void window::set_width_height(uint32_t width, uint32_t height)
    {
        this->width = width;
        this->height = height;
        set_width_height_impl(width, height);
    }

    window::window(const window_properties& props) : name(props.name) {}
}