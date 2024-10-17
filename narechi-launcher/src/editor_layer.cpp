#include "editor_layer.hpp"

#include "panels/content_browser_panel.hpp"

namespace narechi::editor
{
    editor_layer::editor_layer() : layer("EditorLayer") {}

    void editor_layer::on_attach()
    {
        panels.push_back(new content_browser_panel());
    }

    void editor_layer::on_detach()
    {
        for (auto& panel : panels)
        {
            delete panel;
        }

        panels.clear();
    }

    void editor_layer::on_gui_update()
    {
        for (auto& panel : panels)
        {
            panel->render();
        }
    }

    void editor_layer::on_update(float dt) {}

    void editor_layer::on_event(event& event)
    {
        for (auto& panel : panels)
        {
            if (event.handled)
            {
                break;
            }

            panel->on_event(event);
        }
    }

    void editor_layer::set_project(uptr<project> project)
    {
        current_project = std::move(project);
        NRC_CORE_LOG(current_project->get_props().name);
    }
}