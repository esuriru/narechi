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

    void text_input_element::set_text(const std::string& text)
    {
        props.text = text;
    }

    float text_input_element::get_label_length()
    {
        // For GUI libraries that don't have impl this
        return 0.0f;
    }

    text_input_element_properties& text_input_element::get_props()
    {
        return props;
    }

    text_input_element::text_input_element(
        const text_input_element_properties& props)
    {
        // TODO - Verify props
        this->props = props;
    }
}