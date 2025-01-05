#include "imgui/scope/imgui_tree_node_scope.hpp"
#include "gui/scope/tree_node_scope.hpp"

#include "imgui.h"

namespace narechi::scope
{
    imgui_tree_node_scope::imgui_tree_node_scope(
        const gui::scope::tree_node_scope_properties& props)
    {
        imgui_node_open
            = ImGui::TreeNodeEx((void*)props.id, 0, "%s", props.label.c_str());
    }

    imgui_tree_node_scope::~imgui_tree_node_scope()
    {
        if (imgui_node_open)
        {
            ImGui::TreePop();
        }
    }

    bool imgui_tree_node_scope::is_open()
    {
        return imgui_node_open;
    }
}