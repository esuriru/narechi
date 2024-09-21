#include "project_creation_layer.hpp"

#include "narechi.hpp"

namespace narechi::editor
{
    project_creation_layer::project_creation_layer()
        : layer("ProjectCreationLayer")
    {
        project_name_input = gui::text_input_element::create(
            { .width = 400, .label_on_left = true, .label = "Project Name" });
        create_project_button = gui::button_element::create({ .label = "Create",
            .on_click = []()
            {
                NRC_CORE_LOG("Project created");
            } });

        form_window = gui::window::create({ .name = "Project Creation" });

        form_window->add_element(
            gui::text_element::create({ .text = "Create Project" }));
        form_window->add_element(gui::space_element::create({}));
        form_window->add_element(project_name_input);
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