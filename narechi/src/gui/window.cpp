#include "gui/window.hpp"

#include "imgui.h"

namespace narechi::gui
{
    window::window(std::string&& name) : name(std::move(name)) {}

    void window::render()
    {
        ImGui::Begin(name.c_str(), 0);
        ImGui::Text("ad");
        ImGui::End();
    }
}