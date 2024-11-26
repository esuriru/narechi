#pragma once

#include "narechi.hpp"
#include "panels/editor_panel.hpp"

namespace narechi::editor
{
    class build_panel : public editor_panel
    {
    public:
        build_panel();

        void render() override;

    private:
        sptr<gui::window> window;

        sptr<gui::text_input_element> build_directory_input;
        sptr<gui::button_element> build_directory_button;
    };
}