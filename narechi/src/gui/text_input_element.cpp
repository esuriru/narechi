#include "gui/text_input_element.hpp"

#include "imgui/imgui_text_input_element.hpp"

namespace narechi::gui
{
    sptr<text_input_element> text_input_element::create(
        const text_input_element_properties& props)
    {
        // For now there is only ImGui
        return make_sptr<imgui_text_input_element>(props);
    }

    std::string text_input_element::get_text() const
    {
        return props.text;
    }

    text_input_element::text_input_element(
        const text_input_element_properties& props)
    {
        // TODO - Verify props
        this->props = props;
    }
}