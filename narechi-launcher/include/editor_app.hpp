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
            // TODO - Probably not have a new call here
            push_layer(new project_creation_layer());
            // push_layer(new editor::editor_layer());
        }
    };
}
