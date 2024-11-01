#include "gui/table_element.hpp"

#include "imgui/imgui_table_element.hpp"

namespace narechi::gui
{
    sptr<table_element> table_element::create(
        const table_element_properties& props)
    {
        // For now there is only ImGui
        return make_sptr<imgui_table_element>(props);
    }

    table_element::table_element(const table_element_properties& props)
    {
        // TODO - Verify props
        this->props = props;
    }
}