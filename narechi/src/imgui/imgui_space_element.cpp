#include "imgui/imgui_space_element.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_space_element::imgui_space_element(
        const gui::space_element_properties& props)
        : space_element(props)
    {
    }

    void imgui_space_element::render()
    {
        for (int i = 0; i < props.lines; ++i)
        {
            ImGui::NewLine();
        }
    }
}