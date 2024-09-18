#include "imgui/imgui_text_input_element.hpp"

#include "imgui.h" // IWYU pragma: keep (IMGUI_API forward decl)
#include "misc/cpp/imgui_stdlib.h"

namespace narechi
{
    imgui_text_input_element::imgui_text_input_element(
        const gui::text_input_element_properties& props)
        : text_input_element(props)
    {
    }

    void imgui_text_input_element::render()
    {
        if (props.label_on_left)
        {
            ImGui::Text("%s", props.label.c_str());
            ImGui::SameLine();
        }

        ImGui::PushItemWidth(props.width);
        ImGui::InputText(
            props.label_on_left ? "##" : props.label.c_str(), &props.text, 0);
        ImGui::PopItemWidth();
    }
}