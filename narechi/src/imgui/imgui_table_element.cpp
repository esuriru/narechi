#include "imgui/imgui_table_element.hpp"

#include "imgui.h"

namespace narechi
{
    imgui_table_element::imgui_table_element(
        const gui::table_element_properties& props)
        : table_element(props)
    {
    }

    void imgui_table_element::fill_up_row(
        uint32_t row, sptr<gui::element> element)
    {
        // Resize the table if too small
        if (elements.size() - 1 < row)
        {
            for (int i = elements.size(); i < row; ++i)
            {
                elements.push_back(std::vector<sptr<gui::element>>());
            }
        }

        elements[row] = std::vector<sptr<gui::element>>(props.columns, element);
    }

    void imgui_table_element::render()
    {
        if (ImGui::BeginTable(uid.c_str(), props.columns))
        {
            for (uint32_t row = 0; row < props.rows; ++row)
            {
                ImGui::TableNextRow();
                for (uint32_t column = 0; column < props.columns; ++column)
                {
                    ImGui::TableSetColumnIndex(column);
                    // ImGui::Text("Row %d Column %d", row, column);
                    elements[row][column]->render();
                }
            }
            ImGui::EndTable();
        }
    }
}