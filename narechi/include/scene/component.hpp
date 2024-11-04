#pragma once

#include "glm/glm.hpp"
#include "graphics/texture2d.hpp"

namespace narechi::scene
{
    struct position
    {
        glm::vec2 value;
    };

    struct sprite
    {
        sptr<graphics::texture2d> texture;
    };
}