#include "gui/scope/tree_scope.hpp"

#include "imgui/scope/imgui_tree_scope.hpp"

namespace narechi::gui::scope
{
    uptr<tree_scope> tree_scope::create(const tree_scope_properties& props)
    {
        return make_uptr<::narechi::scope::imgui_tree_scope>(props);
    }
}