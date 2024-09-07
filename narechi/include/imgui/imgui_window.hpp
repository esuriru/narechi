#pragma once

#include "gui/element.hpp"
#include "gui/window.hpp"
#include "imgui.h"

#include <vector>

namespace narechi
{
    class imgui_window : public gui::window
    {
    public:
        imgui_window(const gui::window_properties& props);

        void render() override;
        void add_element(uptr<gui::element>&& element) override;

    private:
        ImVec2 position;

        std::vector<uptr<gui::element>> elements;
    };
}