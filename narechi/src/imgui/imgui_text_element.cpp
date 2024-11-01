#include "imgui/imgui_text_element.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_text_element::imgui_text_element(
        const gui::text_element_properties& props)
        : text_element(props)
    {
    }

    void imgui_text_element::set_text(const std::string& text)
    {
        is_dirty = true;
        text_element::set_text(text);
    }

    void imgui_text_element::set_truncate_width(float truncate_width)
    {
        is_dirty = true;
        text_element::set_truncate_width(truncate_width);
    }

    void imgui_text_element::render()
    {
        bool truncate = props.truncate_width.has_value();

        if (truncate && (is_dirty || truncated_string.empty()))
        {
            // Update the cached string
            truncated_string = truncate_text_for_element(
                props.text, props.truncate_width.value());
        }

        ImGui::Text("%s", (truncate ? truncated_string : props.text).c_str());
    }

    std::string imgui_text_element::truncate_text_for_element(
        const std::string& text, float width)
    {
        std::string truncated_text = text;

        const float text_width
            = ImGui::CalcTextSize(text.c_str(), nullptr, true).x;

        if (text_width > width)
        {
            constexpr const char* ellipsis = "...";
            const float ellipsis_size = ImGui::CalcTextSize(ellipsis).x;

            int visible_chars = 0;
            for (size_t i = 0; i < text.size(); i++)
            {
                const float current_width = ImGui::CalcTextSize(
                    text.substr(0, i).c_str(), nullptr, true)
                                                .x;
                if (current_width + ellipsis_size > width)
                {
                    break;
                }

                visible_chars = i;
            }

            truncated_text = (text.substr(0, visible_chars) + ellipsis).c_str();
        }

        return truncated_text;
    }
}