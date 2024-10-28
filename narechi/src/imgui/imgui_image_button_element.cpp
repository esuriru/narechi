#include "imgui/imgui_image_button_element.hpp"

#include "core/logger.hpp"
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
        return ImGui::ImageButton(props.label.c_str(),
            (ImTextureID)(intptr_t)props.texture->get_gfx_ctx_id(),
            ImVec2(props.texture->get_width(), props.texture->get_height()),
            ImVec2(0.0f, 0.0f),
            ImVec2(1.0f, 1.0f));
    }
}
