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

    void window::render(const std::function<void()>& render_pipeline_callback)
    {
        render();
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
        props.width = width;
        props.height = height;
        set_width_height_impl(width, height);
    }

    void window::set_active(bool active)
    {
        this->active = active;
    }

    uint32_t window::get_width()
    {
        return props.width;
    }

    uint32_t window::get_height()
    {
        return props.height;
    }

    window::window(const window_properties& props)
        : props(props)
    {
    }
}