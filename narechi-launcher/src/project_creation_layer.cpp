#include "project_creation_layer.hpp"

#include "gui/text_element.hpp"
#include "gui/text_input_element.hpp"
#include "gui/window.hpp"

namespace narechi::editor
{
    project_creation_layer::project_creation_layer()
        : layer("ProjectCreationLayer")
    {
        project_name_input = gui::text_input_element::create(
            { .width = 400, .label_on_left = true, .label = "Project Name" });

        form_window = gui::window::create({ .name = "Project Creation" });

        form_window->add_element(
            gui::text_element::create({ .text = "Create Project" }));
        form_window->add_element(project_name_input);
    }

    void project_creation_layer::on_attach() {}

    void project_creation_layer::on_detach() {}

    void project_creation_layer::on_gui_update()
    {
        form_window->render();
    }

    void project_creation_layer::on_update(float dt) {}
}