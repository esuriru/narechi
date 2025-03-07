#pragma once

#include "core/core.hpp"
#include "utils/enum_flag_utils.hpp"
#include <cstdint>

#include <string>

namespace narechi::gui::scope
{
    struct tree_node_scope_properties
    {
        unsigned long long id = 0;
        bool selected = false;
        std::string label {};
    };

    class NRC_API tree_node_scope
    {
    public:
        virtual ~tree_node_scope() = default;

        static uptr<tree_node_scope> create(
            const tree_node_scope_properties& props);

        virtual bool is_open() const = 0;
        virtual bool is_clicked() const = 0;

    protected:
        tree_node_scope() = default;
    };
}