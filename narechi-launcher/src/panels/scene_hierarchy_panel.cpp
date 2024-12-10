#include "panels/scene_hierarchy_panel.hpp"

namespace narechi::editor
{
    scene_hierarchy_panel::scene_hierarchy_panel()
        : editor_panel("Scene Hierarchy")
        , window(gui::window::create({ .name = this->name }))
    {
    }

    void scene_hierarchy_panel::render()
    {
        window->render();
    }
}
