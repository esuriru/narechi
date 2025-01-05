#include "imgui/scope/imgui_tree_node_scope.hpp"
#include "gui/scope/tree_node_scope.hpp"

#include "imgui.h"

namespace narechi::scope
{
    imgui_tree_node_scope::imgui_tree_node_scope(
        const gui::scope::tree_node_scope_properties& props)
    {
        ImGuiTreeNodeFlags flags
            = props.selected ? ImGuiTreeNodeFlags_Selected : 0;
        imgui_node_open = ImGui::TreeNodeEx(
            (void*)props.id, flags, "%s", props.label.c_str());
    }

    imgui_tree_node_scope::~imgui_tree_node_scope()
    {
        if (imgui_node_open)
        {
            ImGui::TreePop();
        }
    }

    bool imgui_tree_node_scope::is_open() const
    {
        return imgui_node_open;
    }

    bool imgui_tree_node_scope::is_clicked() const
    {
        return ImGui::IsItemClicked();
    }
}