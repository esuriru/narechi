#include "imgui/imgui_image_element.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_image_element::imgui_image_element(
        const gui::image_element_properties& props)
        : image_element(props)
    {
    }

    void imgui_image_element::render()
    {
        if (props.texture)
        {
            ImGui::Image(reinterpret_cast<void*>(
                             static_cast<intptr_t>(props.texture->get_id())),
                get_image_size());
        }
        else
        {
            ImGui::Image(reinterpret_cast<void*>(
                             static_cast<intptr_t>(props.texture_gfx_ctx_id)),
                ImVec2(props.width, props.height));
        }
    }

    const ImVec2 imgui_image_element::get_image_size()
    {
        return props.width != props.null_size
                && props.height != props.null_size ?
            ImVec2(props.width, props.height) :
            ImVec2(props.texture->get_width(), props.texture->get_height());
    }
}