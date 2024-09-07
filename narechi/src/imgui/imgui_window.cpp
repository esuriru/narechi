#include "imgui/imgui_window.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_window::imgui_window(const gui::window_properties& props)
        : window(props),
          position(ImVec2(props.start_position_x, props.start_position_y))
    {
        set_width_height(props.width, props.height);
    }

    void imgui_window::render()
    {
        ImGui::SetNextWindowSize(size);
        ImGui::SetNextWindowPos(position);
        ImGui::Begin(name.c_str(), 0, ImGuiWindowFlags_NoResize);

        for (auto& elem : elements)
        {
            elem->render();
        }

        ImGui::End();
    }

    void imgui_window::add_element(uptr<gui::element>&& element)
    {
        elements.push_back(std::move(element));
    }

    void imgui_window::set_width_height_impl(uint32_t width, uint32_t height)
    {
        size = ImVec2(width, height);
    }
}
