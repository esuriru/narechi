#pragma once

#include "core/core.hpp"
#include "gui/scope/tree_node_scope.hpp"

#include <string>

// TODO - Fix namespaces
namespace narechi::scope
{
    class NRC_API imgui_tree_node_scope : public gui::scope::tree_node_scope
    {
    public:
        imgui_tree_node_scope(
            const gui::scope::tree_node_scope_properties& props);
        ~imgui_tree_node_scope();

        bool is_open() override;

    private:
        bool imgui_node_open = true;
    };
}