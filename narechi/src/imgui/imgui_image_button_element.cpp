#include "imgui/imgui_image_button_element.hpp"

#include "gui/button_element.hpp"
#include "gui/image_button_element.hpp"
#include "imgui.h"

namespace narechi
{
    imgui_image_button_element::imgui_image_button_element(
        const gui::button_element_properties& props,
        sptr<graphics::texture2d> texture)
        : gui::image_button_element(texture)
        , gui::button_element(props)
    {
    }

    bool imgui_image_button_element::imgui_button_call()
    {
        return ImGui::ImageButton(uid.c_str(),
            reinterpret_cast<ImTextureID>(
                static_cast<intptr_t>(texture->get_id())),
            get_image_size(),
            ImVec2(0.0f, 0.0f),
            ImVec2(1.0f, 1.0f));
    }

    const ImVec2 imgui_image_button_element::get_image_size()
    {
        return props.width != props.null_size
                && props.height != props.null_size ?
            ImVec2(props.width, props.height) :
            ImVec2(texture->get_width(), texture->get_height());
    }
}
