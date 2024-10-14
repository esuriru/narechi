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

    text_element::text_element(const text_element_properties& props)
    {
        // TODO - Verify props
        text = props.text;
    }
}