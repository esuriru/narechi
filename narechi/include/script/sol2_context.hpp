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

        void init(bool open_libs = false);
        void reload();

        template<typename T>
        void set_global(const char* key, T value)
        {
            lua_state[key] = value;
        }

    private:
        sol::state lua_state;

        void init_glm();
    };
}