#include "script/sol2_context.hpp"

#include "sol/sol.hpp"
#include "core/logger.hpp"

namespace narechi::script
{
    sol2_context::sol2_context()
    {
        lua_state.open_libraries(sol::lib::base, sol::lib::package);
        sol::protected_function_result result
            = lua_state.script(R"(print("sol2 initialized"))");
        if (!result.valid())
        {
            NRC_CORE_LOG("sol2 could not initialize");
        }

        // sol::protected_function_result script_result = lua_state.script(R"(
        //     function f(position)
        //         position.x
        //     end()
        // )");
        // lua_state["f"].call();
    }
}
