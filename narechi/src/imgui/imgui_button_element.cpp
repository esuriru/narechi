#include "imgui/imgui_button_element.hpp"

#include "gui/button_element.hpp"
#include "imgui.h"

namespace narechi
{
    imgui_button_element::imgui_button_element(
        const gui::button_element_properties& props)
        : gui::button_element(props)
    {
    }

    bool imgui_button_element::imgui_button_call()
    {
        return ImGui::Button(
            props.label.c_str(), ImVec2(props.width, props.height));
    }

    void imgui_button_element::render()
    {
        if (props.same_line)
        {
            ImGui::SameLine();
        }

        if (imgui_button_call())
        {
            is_pressed_flag = true;
            if (props.on_click)
            {
                props.on_click();
            }
        }
        else
        {
            is_pressed_flag = false;
        }
    }

    bool imgui_button_element::is_pressed() const
    {
        return is_pressed_flag;
    }
}