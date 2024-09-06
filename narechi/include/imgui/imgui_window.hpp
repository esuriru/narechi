#pragma once

#include "gui/window.hpp"
#include "imgui.h"

namespace narechi
{
    class imgui_window : public gui::window
    {
    public:
        imgui_window(const gui::window_properties& props);

        void render() override;

    private:
        ImVec2 position;
    };
}