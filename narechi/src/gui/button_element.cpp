#include "gui/button_element.hpp"

#include "imgui/imgui_button_element.hpp"
#include "imgui/imgui_image_button_element.hpp"

namespace narechi::gui
{
    sptr<button_element> button_element::create(
        const button_element_properties& props)
    {
        // For now there is only ImGui
        return props.texture ? make_sptr<imgui_image_button_element>(props) :
                               make_sptr<imgui_button_element>(props);
    }

    void button_element::set_label(const std::string& label)
    {
        props.label = label;
    }

    void button_element::set_on_click_callback(
        const std::function<void()> callback)
    {
        props.on_click = callback;
    }

    void button_element::set_width(float width)
    {
        props.width = width;
    }

    void button_element::set_height(float height)
    {
        props.height = height;
    }

    button_element::button_element(const button_element_properties& props)
    {
        // TODO - Verify props
        this->props = props;
    }
}