#pragma once

#include "core/layer.hpp"

#include "narechi.hpp"

namespace narechi::editor
{
    class project_creation_layer final : public layer
    {
    public:
        explicit project_creation_layer();

        void on_attach() override;
        void on_detach() override;

        void on_gui_update() override;
        void on_update(float dt) override;

    private:
        uptr<gui::window> form_window;

        sptr<gui::text_input_element> project_name_input;
        sptr<gui::button_element> create_project_button;
    };
}