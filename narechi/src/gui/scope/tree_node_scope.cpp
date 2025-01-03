#include "gui/scope/tree_node_scope.hpp"

#include "imgui/scope/imgui_tree_node_scope.hpp"

namespace narechi::gui::scope
{
    uptr<tree_node_scope> tree_node_scope::create(
        const tree_node_scope_properties& props)
    {
        return make_uptr<::narechi::scope::imgui_tree_node_scope>(props);
    }
}