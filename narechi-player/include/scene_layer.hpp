#pragma once

#include "narechi.hpp"

namespace narechi::player
{
    class scene_layer : public layer
    {
    public:
        scene_layer();

        void on_attach() override;
    };
}