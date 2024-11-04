#pragma once

#include "glm/glm.hpp"
#include "rendering/texture2d.hpp"

namespace narechi::scene
{
    struct position
    {
        glm::vec2 value;
    };

    struct sprite
    {
        sptr<rendering::texture2d> texture;
    };
}