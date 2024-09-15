#include "project_creation_layer.hpp"
#include "gui/text_element.hpp"
#include "gui/window.hpp"

namespace narechi::editor
{
    project_creation_layer::project_creation_layer()
        : layer("ProjectCreationLayer")
    {
        form_window = gui::window::create({ .name = "Project Creation" });
        form_window->add_element(
            gui::text_element::create({ .text = "Create Project " }));
    }

    void project_creation_layer::on_attach() {}

    void project_creation_layer::on_detach() {}

    void project_creation_layer::on_gui_update()
    {
        form_window->render();
    }

    void project_creation_layer::on_update(float dt) {}
}