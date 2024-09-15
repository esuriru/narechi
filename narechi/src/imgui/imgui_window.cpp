#include "imgui/imgui_window.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_window::imgui_window(const gui::window_properties& props)
        : window(props),
          position(ImVec2(props.start_position_x, props.start_position_y))
    {
        if (!props.no_init)
        {
            set_width_height(props.width, props.height);
        }
    }

    void imgui_window::render()
    {
        if (!props.no_init && has_rendered)
        {
            ImGui::SetNextWindowSize(size);
            ImGui::SetNextWindowPos(position);
            has_rendered = false;
        }

        ImGui::Begin(props.name.c_str(), 0, ImGuiWindowFlags_NoResize);
        size = ImGui::GetWindowSize();

        for (auto& elem : elements)
        {
            elem->render();
        }

        ImGui::End();
    }

    void imgui_window::add_element(sptr<gui::element> element)
    {
        elements.push_back(element);
    }

    void imgui_window::set_width_height_impl(uint32_t width, uint32_t height)
    {
        size.x = width;
        size.y = height;
    }
}
