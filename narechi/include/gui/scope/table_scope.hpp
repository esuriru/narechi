#pragma once

#include "core/core.hpp"
#include "utils/enum_flag_utils.hpp"
#include <cstdint>

#include <string>

namespace narechi::gui::scope
{
    enum class table_scope_flags
    {
        none = 0,
        fit_columns_to_width = 1 << 0,
    };

    NRC_ENUM_FLAG_OPERATORS(table_scope_flags)

    struct table_scope_properties
    {
        std::string label;
        uint32_t columns;

        // For `fit_columns_to_width` to work
        uint32_t element_size;
        table_scope_flags flags;
        float padding_x {};
        float padding_y {};
    };

    class NRC_API table_scope
    {
    public:
        virtual ~table_scope() = default;

        static uptr<table_scope> create(const table_scope_properties& props);

        virtual void next_row() = 0;
        virtual void next_column() = 0;

    protected:
        table_scope() = default;
    };
}