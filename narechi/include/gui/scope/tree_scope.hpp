#pragma once

#include "core/core.hpp"
#include "utils/enum_flag_utils.hpp"
#include <cstdint>

#include <string>

namespace narechi::gui::scope
{
    struct tree_scope_properties
    {
        std::string label;
    };

    class NRC_API tree_scope
    {
    public:
        virtual ~tree_scope() = default;

        static uptr<tree_scope> create(const tree_scope_properties& props);

    protected:
        tree_scope() = default;
    };
}