#include "imgui/imgui_menu_bar.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_menu_bar::imgui_menu_bar(const gui::menu_bar_properties& props)
        : menu_bar(props)
    {
    }

    void imgui_menu_bar::render()
    {
        if (ImGui::BeginMainMenuBar())
        {
            for (const auto& menu_item : props.menu_items)
            {
                if (ImGui::BeginMenu(menu_item.title.c_str()))
                {
                    for (auto& sub_menu_item : menu_item.sub_menu_items)
                    {
                        if (ImGui::MenuItem(sub_menu_item.title.c_str()))
                        {
                            sub_menu_item.callback();
                        }
                    }
                    ImGui::EndMenu();
                }
            }
            ImGui::EndMainMenuBar();
        }
    }
}