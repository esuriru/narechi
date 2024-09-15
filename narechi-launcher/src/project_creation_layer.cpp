#include "project_creation_layer.hpp"
#include "gui/window.hpp"

namespace narechi::editor
{
    project_creation_layer::project_creation_layer()
        : layer("ProjectCreationLayer")
    {
        form_window = gui::window::create({ .name = "Project Creation Form" });
    }

    void project_creation_layer::on_attach() {}

    void project_creation_layer::on_detach() {}

    void project_creation_layer::on_gui_update()
    {
        form_window->render();
    }

    void project_creation_layer::on_update(float dt) {}
}