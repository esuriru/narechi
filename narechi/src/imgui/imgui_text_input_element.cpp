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

    float imgui_text_input_element::get_label_length()
    {
        return label_length;
    }

    void imgui_text_input_element::render()
    {
        label_length = props.label.empty() ?
            0.0f :
            ImGui::CalcTextSize(props.label.c_str()).x;

        if (props.label_on_left)
        {
            ImGui::Text("%s", props.label.c_str());
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + props.label_gap);
        }

        if (props.bottom_of_window)
        {
            ImGui::SetCursorPosY(
                ImGui::GetWindowSize().y - props.bottom_margin);
        }

        ImGui::PushItemWidth(props.width);
        // TODO - Create GUID gen and append to double hash
        ImGui::InputText(props.label.empty() ? ("##" + uid).c_str() :
                props.label_on_left          ? ("##" + props.label).c_str() :
                                               props.label.c_str(),
            props.text,
            0);
        ImGui::PopItemWidth();
    }
}