#pragma once

#include <string>

namespace narechi::editor
{
    class editor_panel
    {
    public:
        editor_panel(std::string&& name) : name(std::move(name)) {}
        virtual ~editor_panel() = default;

        virtual void render() = 0;

    protected:
        std::string name;
    };
}