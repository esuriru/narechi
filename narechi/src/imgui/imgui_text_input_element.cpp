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
        ImGui::PushItemWidth(props.width);
        ImGui::InputText(props.label.c_str(), &props.text, 0);
        ImGui::PopItemWidth();
    }
}