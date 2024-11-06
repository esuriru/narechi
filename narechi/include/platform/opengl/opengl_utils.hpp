#pragma once

#include "graphics/format.hpp"
#include "glad/gl.h"

#include "core/logger.hpp"

namespace narechi::utils
{
    constexpr GLenum format_to_opengl_format(const graphics::format format)
    {
        switch (format)
        {
        case graphics::format::r8:
            return GL_R8;
        case graphics::format::rgb8:
            return GL_RGB8;
        case graphics::format::rgba8:
            return GL_RGBA8;
        case graphics::format::rgba32f:
            return GL_RGBA32F;
        default:
            break;
        }

        NRC_CORE_ERROR("Could not translate format to opengl format");
    }
}