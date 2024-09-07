#include "imgui/imgui_text_element.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_text_element::imgui_text_element(
        const gui::text_element_properties& props)
        : text_element(props)
    {
    }

    void imgui_text_element::render()
    {
        ImGui::Text("%s", text.c_str());
    }
}