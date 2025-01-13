#pragma once

#include "core/core.hpp"

#include "sol/sol.hpp"

namespace narechi::script
{
    class NRC_API sol2_context
    {
    public:
        sol2_context();
        sol::state& get_lua_state();

    private:
        sol::state lua_state;
    };
}