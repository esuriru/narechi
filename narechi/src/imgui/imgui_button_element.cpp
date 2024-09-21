#include "imgui/imgui_button_element.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_button_element::imgui_button_element(
        const gui::button_element_properties& props)
        : button_element(props)
    {
    }

    void imgui_button_element::render()
    {
        if (ImGui::Button(props.label.c_str()))
        {
            if (props.on_click)
            {
                props.on_click();
            }
        }
    }
}