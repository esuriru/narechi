#include "imgui/imgui_float_input_element.hpp"

#include "imgui.h" // IWYU pragma: keep (IMGUI_API forward decl)
#include "misc/cpp/imgui_stdlib.h"

namespace narechi
{
    imgui_float_input_element::imgui_float_input_element(
        const gui::float_input_element_properties& props)
        : float_input_element(props)
    {
    }

    float imgui_float_input_element::get_label_length()
    {
        return label_length;
    }

    void imgui_float_input_element::render()
    {
        label_length = props.label.empty() ?
            0.0f :
            ImGui::CalcTextSize(props.label.c_str()).x;

        if (props.same_line)
        {
            ImGui::SameLine();
        }

        if (!props.label.empty() && props.label_on_left)
        {
            ImGui::Text("%s", props.label.c_str());
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + props.label_gap);
        }

        ImGui::PushItemWidth(props.width);
        // TODO - Create GUID gen and append to double hash
        ImGui::InputFloat(props.label_on_left ? ("##" + props.label).c_str() :
                                                props.label.c_str(),
            props.value);
        ImGui::PopItemWidth();
    }
}