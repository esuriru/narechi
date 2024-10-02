#pragma once

#include "project_creation_layer.hpp"
#include "editor_layer.hpp"
#include "narechi.hpp"

namespace narechi::editor
{
    class editor_app : public app
    {
    public:
        editor_app()
        {
            exit_project_creation_callback = [&]()
            {
                // TODO - Submit to a queue to flush these in app
                pop_layer(pc_layer);
                push_layer(create_and_push_layer<editor_layer>());
            };

            pc_layer = create_and_push_layer<project_creation_layer>(
                exit_project_creation_callback);
        }

    private:
        std::function<void()> exit_project_creation_callback;

        sptr<project_creation_layer> pc_layer;
    };
}
