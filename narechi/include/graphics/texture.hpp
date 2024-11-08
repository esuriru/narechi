#pragma once

#include "core/core.hpp"
#include "graphics/handle.hpp"
#include "utils/enum_flag_utils.hpp"

namespace narechi::graphics
{
    class NRC_API texture : public handle
    {
    public:
        enum class filter_mode
        {
            linear,
            nearest
        };

        NRC_MEMBER_ENUM_FLAG_OPERATORS(filter_mode);

        enum class wrap_mode
        {
            repeat,
            clamp_edge,
            clamp_border,
        };

        NRC_MEMBER_ENUM_FLAG_OPERATORS(wrap_mode);

        virtual ~texture() = default;

        virtual void set_min_filter(const filter_mode mode) = 0;
        virtual void set_mag_filter(const filter_mode mode) = 0;

        virtual void set_wrap_s(const wrap_mode mode) = 0;
        virtual void set_wrap_t(const wrap_mode mode) = 0;

        virtual uint32_t get_width() const = 0;
        virtual uint32_t get_height() const = 0;

        virtual void bind(const uint32_t slot = 0) = 0;
        virtual void unbind() = 0;
    };
}
