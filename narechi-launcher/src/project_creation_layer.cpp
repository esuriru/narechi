#include "project_creation_layer.hpp"

#include "narechi.hpp"

namespace narechi::editor
{
    project_creation_layer::project_creation_layer(
        std::function<void()> exit_callback)
        : layer("ProjectCreationLayer")
    {
        project_name_input = gui::text_input_element::create(
            { .width = 400, .label_on_left = true, .label = "Project Name" });
        project_directory_input = gui::text_input_element::create(
            { .width = 400, .label_on_left = true, .label = "Directory" });
        create_project_button = gui::button_element::create({ .label = "Create",
            .on_click = [=]()
            {
                exit_callback();
            } });
        select_directory_button
            = gui::button_element::create({ .same_line = true,
                .label = "Dir",
                .on_click = [this]()
                {
                    std::string folder_path;
                    static auto nfd_ctx = app::get().get_nfd_context();
                    nfd_ctx.pick_folder(folder_path);
                    project_directory_input->set_text(folder_path);
                } });

        form_window = gui::window::create({ .name = "Project Creation",
            .flags = gui::window_flags::align_text_elements });

        form_window->add_element(
            gui::text_element::create({ .text = "Create Project" }));
        form_window->add_element(gui::space_element::create({}));
        form_window->add_element(project_name_input);
        form_window->add_element(project_directory_input);
        form_window->add_element(select_directory_button);
        form_window->add_element(create_project_button);
    }

    void project_creation_layer::on_attach() {}

    void project_creation_layer::on_detach() {}

    void project_creation_layer::on_gui_update()
    {
        form_window->render();
    }

    void project_creation_layer::on_update(float dt) {}
}