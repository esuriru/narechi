#include "gui/text_element.hpp"

#include "imgui/imgui_text_element.hpp"

namespace narechi::gui
{
    sptr<text_element> text_element::create(
        const text_element_properties& props)
    {
        // For now there is only ImGui
        return make_sptr<imgui_text_element>(props);
    }

    void text_element::set_text(const std::string& text)
    {
        props.text = text;
    }

    void text_element::set_scale(float scale)
    {
        props.scale = scale;
    }

    void text_element::set_truncate_width(float truncate_width)
    {
        props.truncate_width = truncate_width;
    }

    text_element::text_element(const text_element_properties& props)
        : props(props)
    {
        // TODO - Verify props
    }
}