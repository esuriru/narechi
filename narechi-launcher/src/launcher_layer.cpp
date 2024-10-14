#include "launcher_layer.hpp"

#include "narechi.hpp"
#include "project.hpp"
#include "yaml-cpp/emitter.h"

#include <filesystem>

namespace narechi::editor
{
    launcher_layer::launcher_layer(std::function<void()> exit_callback)
        : layer("ProjectCreationLayer"),
          main_window(gui::window::create({ .name = "Main" })),
          current_window(*main_window), render_form(false)
    {
        static auto nfd_ctx = app::get().get_nfd_context();

        form_window = gui::window::create({ .name = "Project Creation",
            .flags = gui::window_flags::align_text_elements });

        main_window->add_element(
            gui::button_element::create({ .label = "Create Project",
                .on_click = [&]()
                {
                    render_form = true;
                } }));
        main_window->add_element(
            gui::button_element::create({ .label = "Select Project",
                .on_click = [=, this]()
                {
                    auto file = nfd_ctx.open_file_dialog();
                    exit_callback();
                } }));

        float input_width = 850.0f;
        project_name_input
            = gui::text_input_element::create({ .width = input_width,
                .label_on_left = true,
                .label = "Project Name" });
        project_directory_input
            = gui::text_input_element::create({ .width = input_width,
                .label_on_left = true,
                .label = "Directory" });
        create_project_button = gui::button_element::create({ .label = "Create",
            .on_click = [=, this]()
            {
                std::string project_name = project_name_input->get_text();
                project project({ .name = project_name });
                std::filesystem::path folder_path(
                    project_directory_input->get_text());
                project::serialize(
                    folder_path / (project_name + ".yaml"), project);
                exit_callback();
            } });
        select_directory_button
            = gui::button_element::create({ .same_line = true,
                .label = "Dir",
                .on_click = [this]()
                {
                    static auto nfd_ctx = app::get().get_nfd_context();
                    std::optional<std::string> folder_path
                        = nfd_ctx.pick_folder();
                    if (folder_path.has_value())
                    {
                        project_directory_input->set_text(folder_path.value());
                    }
                } });

        form_window->add_element(
            gui::text_element::create({ .text = "Create Project" }));
        form_window->add_element(gui::space_element::create({}));
        form_window->add_element(project_name_input);
        form_window->add_element(project_directory_input);
        form_window->add_element(select_directory_button);
        form_window->add_element(create_project_button);
    }

    void launcher_layer::on_attach() {}

    void launcher_layer::on_detach() {}

    void launcher_layer::on_gui_update()
    {
        if (render_form)
        {
            form_window->render();
        }
        else
        {
            main_window->render();
        }
    }

    void launcher_layer::on_update(float dt) {}
}