#include "gui/menu_bar.hpp"

#include "imgui/imgui_menu_bar.hpp"

namespace narechi::gui
{
    sptr<menu_bar> menu_bar::create(const menu_bar_properties& props)
    {
        // For now there is only ImGui
        return make_sptr<imgui_menu_bar>(props);
    }

    menu_bar::menu_bar(const menu_bar_properties& props)
    {
        // TODO - Verify props
        this->props = props;
    }
}