#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "flecs.h"
#include "script/sol2_context.hpp"

namespace narechi::script
{
    class NRC_API lua_script
    {
    public:
        lua_script(
            sol2_context& ctx, const std::string& code, flecs::world world);

        std::unordered_map<std::string, std::vector<std::string>>
        get_function_argument_map(const std::string& code);

        void call();

    private:
        sol2_context& ctx;
        flecs::world world;

        std::unordered_map<std::string, std::vector<flecs::entity>>
            component_map;
        flecs::query<> query;
    };
}