#pragma once

#include "core/layer.hpp"

#include "narechi.hpp"
#include "project.hpp"

#include <functional>

namespace narechi::editor
{
    class launcher_layer final : public layer
    {
    public:
        explicit launcher_layer(
            std::function<void(uptr<project>)> exit_callback);

        void on_attach() override;
        void on_detach() override;

        void on_gui_update() override;

    private:
        uptr<gui::window> main_window;
        uptr<gui::window> form_window;
        gui::window& current_window;
        bool render_form;

        sptr<gui::text_input_element> project_name_input;
        sptr<gui::text_input_element> project_directory_input;
        sptr<gui::button_element> create_project_button;
        sptr<gui::button_element> select_directory_button;
    };
}