#pragma once

#include "core/layer.hpp"

#include "narechi.hpp"

#include <functional>

namespace narechi::editor
{
    class launcher_layer final : public layer
    {
    public:
        explicit launcher_layer(std::function<void()> exit_callback);

        void on_attach() override;
        void on_detach() override;

        void on_gui_update() override;
        void on_update(float dt) override;

    private:
        uptr<gui::window> form_window;

        sptr<gui::text_input_element> project_name_input;
        sptr<gui::text_input_element> project_directory_input;
        sptr<gui::button_element> create_project_button;
        sptr<gui::button_element> select_directory_button;
    };
}