#pragma once

#include "core/logger.hpp"

#include <cstdint>

namespace narechi::graphics
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

    constexpr const char* shader_data_type_to_string(
        const shader_data_type type)
    {
        switch (type)
        {
        case shader_data_type::float1:
            return "float1";
        case shader_data_type::int1:
            return "int1";
        case shader_data_type::bool1:
            return "bool1";
        case shader_data_type::float2:
            return "float2";
        case shader_data_type::int2:
            return "int2";
        case shader_data_type::float3:
            return "float3";
        case shader_data_type::int3:
            return "int3";
        case shader_data_type::float4:
            return "float4";
        case shader_data_type::int4:
            return "int4";
        case shader_data_type::mat3:
            return "mat3";
        case shader_data_type::mat4:
            return "mat4";
        default:
            break;
        }

        NRC_CORE_FATAL(
            "shader data type not handled, shader data type (not converted): ",
            std::to_string(static_cast<int>(type)));
        return 0;
    }

    constexpr uint32_t shader_data_type_component_count(
        const shader_data_type type)
    {
        switch (type)
        {
        case shader_data_type::float1:
        case shader_data_type::int1:
        case shader_data_type::bool1:
            return 1;
        case shader_data_type::float2:
        case shader_data_type::int2:
            return 2;
        case shader_data_type::float3:
        case shader_data_type::int3:
            return 3;
        case shader_data_type::float4:
        case shader_data_type::int4:
            return 4;
        case shader_data_type::mat3:
            return 3 * 3;
        case shader_data_type::mat4:
            return 4 * 4;
        default:
            break;
        }

        NRC_CORE_FATAL("shader data type not handled, shader data type: ",
            shader_data_type_to_string(type));
        return 0;
    }

    constexpr uint32_t shader_data_type_size(const shader_data_type type)
    {
        constexpr uint32_t float_size = 4;

        switch (type)
        {
        case shader_data_type::bool1:
            // One byte
            return 1;
        default:
            return float_size * shader_data_type_component_count(type);
        }

        NRC_CORE_FATAL("shader data type not handled, shader data type: ",
            shader_data_type_to_string(type));
        return 0;
    }
}