#pragma once

#include "editor_layer.hpp"
#include "narechi.hpp"

namespace narechi::editor
{
    class editor_app : public app
    {
    public:
        editor_app()
        {
            push_layer(new editor::editor_layer());
        }
    };
}
