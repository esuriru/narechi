#pragma once

#include <string>

#include <rendering/shader_type.hpp>

namespace narechi
{
    struct buffer_element
    {
        std::string name;
        shader_data_type type;
    };
}