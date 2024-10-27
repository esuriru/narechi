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

        void begin();
        void end();

        void render() override;
        void render(
            const std::function<void()>& render_pipeline_callback) override;
        
        void render_elements();

        void add_element(sptr<gui::element> element) override;
        void add_element(sptr<gui::text_input_element> element) override;
        void set_width_height_impl(uint32_t width, uint32_t height) override;

    private:
        void align_text_input_elements();

        bool is_dirty = true;
        ImVec2 position;
        ImVec2 size;

        std::vector<sptr<gui::text_input_element>> text_input_elements;
        std::vector<sptr<gui::element>> elements;

        std::function<void()> default_render_elements_callback;
    };
}