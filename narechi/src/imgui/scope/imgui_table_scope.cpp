#include "imgui/scope/imgui_table_scope.hpp"
#include "gui/scope/table_scope.hpp"
#include "imgui.h"

namespace narechi::scope
{
    imgui_table_scope::imgui_table_scope(
        const gui::scope::table_scope_properties& props)
        : width(props.element_size)
    {
        ImGui::BeginTable(props.label.c_str(),
            props.flags & gui::scope::table_scope_flags::fit_columns_to_width ?
                std::max(static_cast<int>(ImGui::GetContentRegionAvail().x
                             / props.element_size),
                    1) :
                props.columns,
            ImGuiTableColumnFlags_WidthFixed,
            ImVec2(0.0f, 0.0f),
            props.element_size);
    }

    imgui_table_scope::~imgui_table_scope()
    {
        ImGui::EndTable();
    }

    void imgui_table_scope::next_row()
    {
        ImGui::TableNextRow();
    }

    void imgui_table_scope::next_column()
    {
        ImGui::TableNextColumn();
    }
}