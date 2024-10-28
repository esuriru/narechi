#pragma once

#include "gui/button_element.hpp"

namespace narechi
{
    class NRC_API imgui_button_element : public gui::button_element
    {
    public:
        imgui_button_element(const gui::button_element_properties& props);

        virtual bool imgui_button_call();
        void render() override;

        bool is_pressed() const override;

    protected:
        bool is_pressed_flag;
    };
}