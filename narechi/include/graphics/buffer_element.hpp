#pragma once

#include "graphics/shader_data_type.hpp"

#include <string>

namespace narechi::graphics
{
    struct buffer_element
    {
        std::string name;
        shader_data_type type;
        uint32_t size;
        uint32_t offset;
        bool normalized;

        buffer_element(shader_data_type type, const std::string& name,
            const bool normalized = false);

        constexpr uint32_t get_component_count() const
        {
            return shader_data_type_component_count(type);
        }
    };
}