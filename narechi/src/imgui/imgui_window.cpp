#include "imgui/imgui_window.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_window::imgui_window(const gui::window_properties& props)
        : window(props),
          position(ImVec2(props.start_position_x, props.start_position_y))
    {
    }

    void imgui_window::render()
    {
        ImGui::SetNextWindowPos(position);
        ImGui::Begin(name.c_str(), 0);
        ImGui::Text("imgui window text");
        ImGui::End();
    }
}
