#include "gui/space_element.hpp"

#include "imgui/imgui_space_element.hpp"

namespace narechi::gui
{
    sptr<space_element> space_element::create(
        const space_element_properties& props)
    {
        // For now there is only ImGui
        return make_sptr<imgui_space_element>(props);
    }

    space_element::space_element(const space_element_properties& props)
    {
        // TODO - Verify props
        this->props = props;
    }
}