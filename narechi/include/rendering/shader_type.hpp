#pragma once

#include "core/assert.hpp"

#include <cstdint>

namespace narechi
{
    enum class shader_data_type
    {
        none = 0,
        float1,
        float2,
        float3,
        float4,
        mat3,
        mat4,
        int1,
        int2,
        int3,
        int4,
        bool1,
    };

    constexpr uint32_t shader_data_type_size(shader_data_type type)
    {
        switch (type)
        {
        case shader_data_type::float1:
            return 4;
        case shader_data_type::float2:
            return 4 * 2;
        case shader_data_type::float3:
            return 4 * 3;
        case shader_data_type::float4:
            return 4 * 4;
        case shader_data_type::mat3:
            return 4 * 3 * 3;
        case shader_data_type::mat4:
            return 4 * 4 * 4;
        case shader_data_type::int1:
            return 4;
        case shader_data_type::int2:
            return 4 * 2;
        case shader_data_type::int3:
            return 4 * 3;
        case shader_data_type::int4:
            return 4 * 4;
        case shader_data_type::bool1:
            return 1;
        default:
            break;
        }

        NRC_CORE_FATAL(
            "shader data type not handled, shader data type: ", type);
        return 0;
    }
}