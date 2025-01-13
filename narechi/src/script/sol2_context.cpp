#include "script/sol2_context.hpp"

#include "sol/sol.hpp"
#include "core/logger.hpp"
#include "script/lua_script.hpp"

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

        sol::protected_function_result script_result = lua_state.script(R"(
            function f()
                print("test")
            end
        )");
        lua_state["f"].call();

        lua_script script(R"(
            function f(testarg1, testarg2)
                print("test")
            end
        )");
    }

    sol::state& sol2_context::get_lua_state()
    {
        return lua_state;
    }
}
