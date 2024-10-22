#pragma once

#pragma once

#include "core/core.hpp"

#include "flecs.h"

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
    };
}