#pragma once

#include "core/core.hpp"
#include "gui/scope/tree_scope.hpp"

#include <string>

// TODO - Fix namespaces
namespace narechi::scope
{
    class NRC_API imgui_tree_scope : public gui::scope::tree_scope
    {
    public:
        imgui_tree_scope(const gui::scope::tree_scope_properties& props);
        ~imgui_tree_scope();

    private:
        bool is_created = true;
    };
}