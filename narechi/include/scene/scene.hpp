#pragma once

#pragma once

#include "core/core.hpp"

#include "flecs.h"

NRC_FORWARD_DECL_CLASS(narechi::asset, scene_asset);

namespace narechi::scene
{
    class NRC_API scene
    {
    public:
        scene();
        ~scene();

        void awake();
        void update(float delta_time);

    private:
        flecs::world world;

        friend class asset::scene_asset;
    };
}