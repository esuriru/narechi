#include "script/lua_script.hpp"

#include "core/app.hpp"
#include "core/logger.hpp"
#include "script/raw_component_view.hpp"

#include <unordered_map>
#include <regex>
#include <algorithm>

namespace narechi::script
{
    using std::string;
    using std::unordered_map;
    using std::vector;

    lua_script::lua_script(
        sol2_context& ctx, const std::string& code, flecs::world world)
    {
        auto& lua_state = ctx.get_lua_state();
        sol::protected_function_result result = lua_state.script(code);
        NRC_ASSERT(result.valid(), "Could not compile lua script");

        auto map = get_function_argument_map(code);

        for (auto& kv_pair : map)
        {
            if (kv_pair.second.empty())
            {
                NRC_CORE_LOG("No function arguments detected, skipping");
            }

            NRC_CORE_LOG(
                "Creating query from script function: ", kv_pair.first);

            auto builder = world.query_builder();

            NRC_CORE_LOG("Validating arguments in world");

            unordered_map<string, std::vector<flecs::entity>> component_map;

            int i = 0;
            for (auto& arg : kv_pair.second)
            {
                NRC_CORE_LOG("Querying ", arg, "in world");
                flecs::entity component_entity = world.lookup(arg.c_str());
                if (component_entity <= 0)
                {
                    NRC_CORE_LOG(arg,
                        " does not exist in world, unable to create query");
                }
                component_map[kv_pair.first].push_back(component_entity);

                NRC_CORE_LOG(
                    "Valid query argument ", std::to_string(i++), ": ", arg);
                builder.with(arg.c_str());
            }

            auto query = builder.cached().build();

            query.each(
                [&](flecs::iter& it, size_t row)
                {
                    flecs::entity e = it.entity(row);

                    for (auto& kv_pair : component_map)
                    {
                        std::vector<raw_component_view> raw_components;
                        for (auto& component : kv_pair.second)
                        {
                            void* ptr = e.ensure(component);
                            raw_components.push_back(
                                raw_component_view(world, component, ptr));
                        }

                        sol::function func = lua_state[kv_pair.first];
                        func(sol::as_args(raw_components));
                    }
                });
        }
    }

    vector<string> split(const string& str, const string& delim)
    {
        vector<string> tokens;
        size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if (pos == string::npos)
                pos = str.length();
            string token = str.substr(prev, pos - prev);
            if (!token.empty())
                tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }

    unordered_map<string, vector<string>> lua_script::get_function_argument_map(
        const string& code)
    {
        unordered_map<string, vector<string>> map;
        std::regex function_regex("function\\s+(\\w+)\\s*\\((.*?)\\)");
        std::smatch match;

        string::const_iterator begin = code.begin();
        string::const_iterator end = code.end();

        while (regex_search(begin, end, match, function_regex))
        {
            string function_name = match[1].str();
            string arguments = match[2].str();

            // Split arguments by commas
            vector<string> args = split(arguments, ",");
            for (auto& arg : args)
            {
                arg.erase(std::remove_if(arg.begin(), arg.end(), ::isspace),
                    arg.end());
            }

            map[function_name] = args;
            begin = match.suffix().first;
        }

        return map;
    }
}
