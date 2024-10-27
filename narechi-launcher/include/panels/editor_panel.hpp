#pragma once

#include "narechi.hpp"

#include <string>

namespace narechi::editor
{
    class editor_panel
    {
    public:
        editor_panel(std::string&& name);
        virtual ~editor_panel() = default;

        virtual void render() = 0;
        virtual void on_event(event& event)
        {
        }

        const std::string& get_name();

    protected:
        std::string name;
    };
}