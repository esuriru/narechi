#pragma once

#include "core/core.hpp"
#include "gui/scope/table_scope.hpp"

#include <string>

// TODO - Fix namespaces
namespace narechi::scope
{
    class NRC_API imgui_table_scope : public gui::scope::table_scope
    {
    public:
        imgui_table_scope(const gui::scope::table_scope_properties& props);
        ~imgui_table_scope();

        void next_row() override;
        void next_column() override;

    private:
        float width;
        bool first_column = true;
    };
}