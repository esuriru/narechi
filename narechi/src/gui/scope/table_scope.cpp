#include "gui/scope/table_scope.hpp"

#include "imgui/scope/imgui_table_scope.hpp"

namespace narechi::gui::scope
{
    uptr<table_scope> table_scope::create(const table_scope_properties& props)
    {
        return make_uptr<::narechi::scope::imgui_table_scope>(props);
    }
}