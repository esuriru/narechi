#pragma once

#include "editor_layer.hpp"
#include "narechi.hpp"

// TODO:
// https://www.youtube.com/watch?v=88dmtleVywk&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=11

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
