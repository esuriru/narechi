#pragma once

#include "rendering/shader_type.hpp"

#include <string>

namespace narechi
{
    struct buffer_element
    {
        std::string name;
        shader_data_type type;
    };
}