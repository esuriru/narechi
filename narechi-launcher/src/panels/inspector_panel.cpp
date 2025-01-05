#include "panels/inspector_panel.hpp"

#include "scene/component.hpp"
#include <stack>

namespace narechi::editor
{
    inspector_panel::inspector_panel()
        : editor_panel("Inspector")
        , window(gui::window::create({ .name = this->name }))
    {
    }

    void inspector_panel::render()
    {
        window->render();
    }
}
