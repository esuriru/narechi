#pragma once

#include "gui/button_element.hpp"

namespace narechi
{
    class NRC_API imgui_button_element : public virtual gui::button_element
    {
    public:
        imgui_button_element(const gui::button_element_properties& props);

        virtual bool imgui_button_call();
        void render() override;

        bool is_pressed() override;
        bool is_double_clicked() override;

    protected:
        imgui_button_element() = default;

        bool is_pressed_flag = false;
        bool is_double_clicked_flag = false;
    };
}