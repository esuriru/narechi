#include "imgui/scope/imgui_tree_scope.hpp"
#include "gui/scope/tree_scope.hpp"

#include "imgui.h"

namespace narechi::scope
{
    imgui_tree_scope::imgui_tree_scope(
        const gui::scope::tree_scope_properties& props)
    {
        is_created = ImGui::TreeNode(props.label.c_str());
    }

    imgui_tree_scope::~imgui_tree_scope()
    {
        if (is_created)
        {
            ImGui::TreePop();
        }
    }
}