#include "imgui/imgui_window.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_window::imgui_window(const gui::window_properties& props)
        : window(props)
    {
    }

    void imgui_window::render()
    {
        ImGui::Begin(name.c_str(), 0);
        ImGui::Text("imgui window text");
        ImGui::End();
    }
}
