#pragma once

#include "launcher_layer.hpp"
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
                pop_layer(pc_layer);
                create_and_push_layer<editor_layer>();
            };

            pc_layer = create_and_push_layer<launcher_layer>(
                exit_project_creation_callback);
        }

    private:
        std::function<void()> exit_project_creation_callback;

        sptr<launcher_layer> pc_layer;
    };
}
