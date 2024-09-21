#include "gui/button_element.hpp"

#include "imgui/imgui_button_element.hpp"

namespace narechi::gui
{
    sptr<button_element> button_element::create(
        const button_element_properties& props)
    {
        // For now there is only ImGui
        return make_sptr<imgui_button_element>(props);
    }

    button_element::button_element(const button_element_properties& props)
    {
        // TODO - Verify props
        this->props = props;
    }
}