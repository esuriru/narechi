#pragma once

#include "graphics/texture2d.hpp"

#include "glm/glm.hpp"

namespace narechi::graphics::render2d
{
    void init();

    NRC_API void set_view_matrix(const glm::mat4& mat);
    NRC_API void set_proj_matrix(const glm::mat4& mat);

    NRC_API void submit_quad(
        const glm::vec2& world_pos, sptr<graphics::texture2d> texture);
}