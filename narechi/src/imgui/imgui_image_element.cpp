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
                get_image_size(),
                calc_uv0(),
                calc_uv1());
        }
        else
        {
            ImGui::Image(reinterpret_cast<void*>(
                             static_cast<intptr_t>(props.texture_gfx_ctx_id)),
                ImVec2(props.width, props.height),
                calc_uv0(),
                calc_uv1());
        }
    }

    const ImVec2 imgui_image_element::get_image_size()
    {
        return props.width != props.null_size
                && props.height != props.null_size ?
            ImVec2(props.width, props.height) :
            ImVec2(props.texture->get_width(), props.texture->get_height());
    }

    const ImVec2 imgui_image_element::calc_uv0()
    {
        return props.flip_vertically ? ImVec2(0.0f, 1.0f) : ImVec2(0.0f, 0.0f);
    }

    const ImVec2 imgui_image_element::calc_uv1()
    {
        return props.flip_vertically ? ImVec2(1.0f, 0.0f) : ImVec2(1.0f, 1.0f);
    }
}