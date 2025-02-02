#include "script/lua_script.hpp"

#include "core/app.hpp"
#include "core/logger.hpp"
#include "script/raw_component_view.hpp"
#include "utils/file_utils.hpp"

#include <unordered_map>
#include <regex>
#include <algorithm>
#include <unordered_set>

namespace
{
    using std::string;
    using std::vector;

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
}

namespace narechi::script
{
    using std::string;
    using std::unordered_map;
    using std::vector;

    lua_script::lua_script(const lua_script_deps& deps, const std::string& code)
        : deps(deps)
        , code(code)
    {
        compile();
    }

    lua_script::~lua_script()
    {
    }

    unordered_map<string, vector<string>> lua_script::get_function_argument_map(
        const string& code)
    {
        // NOTE - Depends on lua script actually being run
        auto& lua_state = deps.ctx.get_lua_state();
        sol::table global_table = lua_state.globals();

        std::unordered_set<std::string> function_names {};

        for (auto& pair : global_table)
        {
            if (pair.second.get_type() == sol::type::function)
            {
                function_names.insert(pair.first.as<std::string>());
            }
        }

        if (function_names.empty())
        {
            return {};
        }

        unordered_map<string, vector<string>> map;
        std::regex function_regex("function\\s+(\\w+)\\s*\\((.*?)\\)");

        std::smatch match;

        string::const_iterator begin = code.begin();
        string::const_iterator end = code.end();

        while (regex_search(begin, end, match, function_regex))
        {
            string function_name = match[1].str();
            string arguments = match[2].str();

            if (!function_names.contains(function_name))
            {
                begin = match.suffix().first;
                continue;
            }

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

    void lua_script::call(func_type type)
    {
        auto& lua_state = deps.ctx.get_lua_state();

        auto& query_list = queries[type];

        for (int i = 0; i < query_list.size(); ++i)
        {
            auto& query = query_list[i];

            NRC_ASSERT(deps.world.is_alive(query),
                "Query is not valid in lua script call");

            query.each(
                [&](flecs::iter& it, size_t row)
                {
                    flecs::entity e = it.entity(row);

                    auto& components = component_map[type][i];
                    vector<raw_component_view> raw_components;
                    raw_components.reserve(components.size());
                    for (auto& component : components)
                    {
                        void* ptr = e.ensure(component);
                        raw_components.push_back(
                            raw_component_view(deps.world, component, ptr));
                    }

                    sol::function func = lua_state[function_names[type][i]];
                    func(sol::as_args(raw_components));
                });
        }
    }

    void lua_script::reset()
    {
        component_map.clear();

        for (auto& query_list : queries)
        {
            for (auto& query : query_list.second)
            {
                if (query != 0)
                {
                    query.destruct();
                }
            }
        }

        queries.clear();

        auto& lua_state = deps.ctx.get_lua_state();
        sol::table global_table = lua_state.globals();

        // Clear all functions
        for (auto& name_list : function_names)
        {
            for (auto& name : name_list.second)
            {
                global_table[name] = sol::nil;
            }
        }
        function_names.clear();
    }

    void lua_script::compile()
    {
        // TODO - Cache the same query if it has the same component map

        auto& world = deps.world;
        auto& ctx = deps.ctx;

        auto& lua_state = ctx.get_lua_state();

        sol::protected_function_result result = lua_state.script(code);
        NRC_ASSERT(result.valid(), "Could not compile lua script");

        auto map = get_function_argument_map(code);

        constexpr std::string_view double_underscore = "__";
        constexpr std::string_view dot = ".";

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

            // Create empty list
            func_type type = kv_pair.first.starts_with("init") ?
                func_type::init :
                func_type::update;
            component_map[type].push_back({});

            int i = 0;
            for (auto& arg : kv_pair.second)
            {
                std::regex pattern("__");
                arg = std::regex_replace(arg, pattern, "::");

                NRC_CORE_LOG("Querying ", arg, " in world");
                flecs::entity component_entity = world.lookup(arg.c_str());
                if (component_entity <= 0)
                {
                    NRC_CORE_LOG(arg,
                        " does not exist in world, unable to create query");
                    return;
                }
                component_map[type].back().push_back(component_entity);

                NRC_CORE_LOG(
                    "Valid query argument ", std::to_string(i++), ": ", arg);
                builder.with(component_entity);
            }

            NRC_CORE_LOG("Generating query: ", kv_pair.first);
            add_to_queries(kv_pair.first, builder.cached().build());
        }
    }

    std::string lua_script::get_code() const
    {
        return code;
    }

    void lua_script::set_code(const std::string& code)
    {
        this->code = code;
    }

    const char* lua_script::extension()
    {
        return ".lua";
    }

    void lua_script::add_to_queries(
        const std::string& query_name, flecs::query<> query)
    {
        func_type type = query_name.starts_with("init") ? func_type::init :
                                                          func_type::update;
        insert_to_query_map(type, query);
        if (function_names.find(type) == function_names.end())
        {
            function_names[type] = {};
        }

        function_names[type].push_back(query_name);
    }

    void lua_script::insert_to_query_map(func_type type, flecs::query<> query)
    {
        // Create a new empty vector if doesn't exist
        if (queries.find(type) == queries.end())
        {
            queries[type] = {};
        }

        queries[type].push_back(query);
    }
}
