#include "imgui/imgui_window.hpp"

#include "gui/text_input_element.hpp"
#include "gui/window.hpp"
#include "imgui.h"

#include <limits>

namespace narechi
{
    imgui_window::imgui_window(const gui::window_properties& props)
        : window(props)
        , position(ImVec2(props.start_position_x, props.start_position_y))
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

        if (is_dirty)
        {
            is_dirty = false;
            if (props.flags & gui::window_flags::align_text_elements)
            {
                align_text_input_elements();
            }
        }

        ImGui::End();
    }

    void imgui_window::add_element(sptr<gui::element> element)
    {
        is_dirty = true;
        elements.push_back(element);
    }

    void imgui_window::add_element(sptr<gui::text_input_element> element)
    {
        is_dirty = true;
        text_input_elements.push_back(element);

        elements.push_back(element);
    }

    void imgui_window::set_width_height_impl(uint32_t width, uint32_t height)
    {
        size.x = width;
        size.y = height;
    }

    void imgui_window::align_text_input_elements()
    {
        float max_length = std::numeric_limits<float>::min();

        for (const auto& element : text_input_elements)
        {
            float length = element->get_label_length();
            if (max_length < length)
            {
                max_length = length;
            }
        }

        for (auto& element : text_input_elements)
        {
            element->get_props().label_gap
                = max_length - element->get_label_length();
        }
    }
}
