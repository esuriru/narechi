#pragma once

#include "gui/image_button_element.hpp"
#include "imgui/imgui_button_element.hpp"

struct ImVec2;

namespace narechi
{
    class NRC_API imgui_image_button_element
        : public imgui_button_element,
          public virtual gui::image_button_element
    {
    public:
        imgui_image_button_element(const gui::button_element_properties& props,
            sptr<rendering::texture2d> texture);

        bool imgui_button_call() override;

    private:
        const ImVec2 get_image_size();
    };
}