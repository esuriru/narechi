#include "script/sol2_context.hpp"

#include "sol/sol.hpp"
#include "core/logger.hpp"
#include "script/lua_script.hpp"
#include "script/raw_component_view.hpp"

namespace narechi::script
{
    sol2_context::sol2_context()
    {
        init(true);
        NRC_CORE_LOG("sol2 initialized");
    }

    sol::state& sol2_context::get_lua_state()
    {
        return lua_state;
    }

    void sol2_context::init(bool open_libs)
    {
        if (open_libs)
        {
            lua_state.open_libraries(sol::lib::base, sol::lib::package);
        }

        lua_state.new_usertype<raw_component_view>("raw_component_view",
            sol::no_constructor,
            "get_float",
            &raw_component_view::get_float,
            "set_float",
            &raw_component_view::set_float,
            "get_float_depth",
            &raw_component_view::get_float_depth,
            "set_float_depth",
            &raw_component_view::set_float_depth);
    }

    void sol2_context::reload()
    {
        lua_state.globals().clear();
        init(true);
    }
}
