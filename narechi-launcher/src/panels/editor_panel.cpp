#include "panels/editor_panel.hpp"

namespace narechi::editor
{
    editor_panel::editor_panel(std::string&& name)
        : name(std::move(name))
    {
    }

    const std::string& editor_panel::get_name()
    {
        return name;
    }
}