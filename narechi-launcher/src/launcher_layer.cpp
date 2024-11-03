#include "launcher_layer.hpp"

#include "gui/button_element.hpp"
#include "narechi.hpp"
#include "project.hpp"
#include "file_extensions.hpp"

#include <filesystem>

namespace narechi::editor
{
    launcher_layer::launcher_layer(
        std::function<void(uptr<project>)> exit_callback)
        : layer("ProjectCreationLayer")
        , main_window(gui::window::create({ .name = "Main" }))
        , current_window(*main_window)
        , render_form(false)
    {
        form_window = gui::window::create({
            .name = "Project Creation",
            .flags = gui::window_flags::align_text_elements,
        });

        main_window->add_element(gui::button_element::create({
            .label = "Create Project",
            .on_click =
                [this]()
            {
                render_form = true;
            },
        }));
        main_window->add_element(gui::button_element::create({
            .label = "Select Project",
            .on_click =
                [exit_callback, this]()
            {
                auto folder_path = utils::file::pick_folder();
                if (!folder_path.has_value())
                {
                    return;
                }

                std::filesystem::path path {};
                for (const auto& it :
                    std::filesystem::directory_iterator(folder_path.value()))
                {
                    if (it.is_regular_file()
                        && it.path().extension() == project_file_extension)
                    {
                        path = it.path();
                    }
                }

                if (path.empty())
                {
                    NRC_CORE_LOG("No project file found in project folder");
                    return;
                }

                exit_callback(project::load(path));
            },
        }));

        float input_width = 850.0f;
        project_name_input = gui::text_input_element::create({
            .width = input_width,
            .label_on_left = true,
            .label = "Project Name",
        });
        project_directory_input = gui::text_input_element::create({
            .width = input_width,
            .label_on_left = true,
            .label = "Directory",
        });
        create_project_button = gui::button_element::create({
            .label = "Create",
            .on_click =
                [exit_callback, this]()
            {
                std::string project_name = project_name_input->get_text();
                std::filesystem::path folder_path(
                    project_directory_input->get_text());

                uptr<project> new_project = project::create(
                    folder_path / (project_name + project_file_extension),
                    project_name);

                exit_callback(std::move(new_project));
            },
        });
        select_directory_button = gui::button_element::create({
            .same_line = true,
            .label = "Dir",
            .on_click =
                [this]()
            {
                auto folder_path = utils::file::pick_folder();
                if (folder_path.has_value())
                {
                    project_directory_input->set_text(folder_path.value());
                }
            },
        });

        form_window->add_element(gui::text_element::create({
            .text = "Create Project",
        }));
        form_window->add_element(gui::space_element::create({}));
        form_window->add_element(project_name_input);
        form_window->add_element(project_directory_input);
        form_window->add_element(select_directory_button);
        form_window->add_element(create_project_button);
        form_window->add_element(gui::button_element::create({
            .same_line = true,
            .label = "Back",
            .on_click =
                [this]()
            {
                render_form = false;
            },
        }));
    }

    void launcher_layer::on_attach()
    {
    }

    void launcher_layer::on_detach()
    {
    }

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
}