#pragma once

#include "glm/glm.hpp"
#include "graphics/texture2d.hpp"

namespace narechi::scene
{
    struct position
    {
        glm::vec2 value = glm::vec2(0.0f, 0.0f);
    };

    struct scene_camera
    {
    };

    struct sprite
    {
        sptr<graphics::texture2d> texture;
    };
}