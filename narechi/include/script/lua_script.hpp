#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "flecs.h"
#include "script/sol2_context.hpp"

namespace narechi::script
{
    class lua_script
    {
    public:
        lua_script(
            sol2_context& ctx, const std::string& code, flecs::world world);

        std::unordered_map<std::string, std::vector<std::string>>
        get_function_argument_map(const std::string& code);
    };
}