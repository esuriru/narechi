#pragma once

#include "narechi.hpp"

#include "scene_layer.hpp"

namespace narechi::player
{
    class player_app : public narechi::app
    {
    public:
        player_app()
        {
            create_and_push_layer<scene_layer>();
        }
    };
}