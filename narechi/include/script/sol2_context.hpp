#pragma once

#include "core/core.hpp"

#include "sol/sol.hpp"

namespace narechi::script
{
    class NRC_API sol2_context
    {
    public:
        sol2_context();

    private:
        sol::state lua_state;
    };
}