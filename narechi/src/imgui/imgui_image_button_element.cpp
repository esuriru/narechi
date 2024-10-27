#include "imgui/imgui_image_button_element.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_image_button_element::imgui_image_button_element(
        const gui::button_element_properties& props)
        : imgui_button_element(props)
    {
    }

    bool imgui_image_button_element::imgui_button_call()
    {
        // ImGui::ImageButton()
    }
}
