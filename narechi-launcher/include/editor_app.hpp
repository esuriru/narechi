#pragma once

#include "launcher_layer.hpp"
#include "editor_layer.hpp"
#include "project.hpp"
#include "narechi.hpp"

namespace narechi::editor
{
    class editor_app : public app
    {
    public:
        editor_app()
        {
            // Pass in callback to change to the editor layer with the project
            // from the launcher layer
            pc_layer = create_and_push_layer<launcher_layer>(
                [&](uptr<project> project)
                {
                    pop_layer(pc_layer);
                    auto editor = create_and_push_layer<editor_layer>();
                    editor->set_project(std::move(project));
                });
        }

    private:
        sptr<launcher_layer> pc_layer;
    };
}
