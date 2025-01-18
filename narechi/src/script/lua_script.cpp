#include "script/lua_script.hpp"

#include "core/app.hpp"
#include "core/logger.hpp"
#include "script/raw_component_view.hpp"
#include "utils/file_utils.hpp"

#include <unordered_map>
#include <regex>
#include <algorithm>

namespace narechi::script
{
    using std::string;
    using std::unordered_map;
    using std::vector;

    lua_script::lua_script(const lua_script_deps& deps, const std::string& code)
        : deps(deps)
        , code(code)
    {
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
                component_map[kv_pair.first].push_back(component_entity);

                NRC_CORE_LOG(
                    "Valid query argument ", std::to_string(i++), ": ", arg);
                builder.with(component_entity);
            }

            NRC_CORE_LOG("Generating query");
            query = builder.cached().build();
        }
    }

    lua_script::~lua_script()
    {
    }

    // sptr<lua_script> lua_script::load_new_meta_s(
    //     const lua_script_deps& deps, const std::filesystem::path& code_path)
    // {
    //     NRC_ASSERT(
    //         std::filesystem::exists(code_path), "Code path does not exist");
    //     std::string code = utils::file::open_file_as_string(code_path);

    //     std::filesystem::path meta_path = code_path;
    //     meta_path.replace_extension(
    //         asset::extension<asset::lua_script_meta_asset>::value);
    //     auto script = make_sptr<lua_script>(deps, code);
    //     script->asset = asset::lua_script_meta_asset::create(meta_path);
    //     return script;
    // }

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

    void lua_script::call()
    {
        auto& lua_state = deps.ctx.get_lua_state();

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
                            raw_component_view(deps.world, component, ptr));
                    }

                    sol::function func = lua_state[kv_pair.first];
                    func(sol::as_args(raw_components));
                }
            });
    }

    void lua_script::compile()
    {
        auto& ctx = deps.ctx;

        auto& lua_state = ctx.get_lua_state();
        sol::protected_function_result result = lua_state.script(code);
        NRC_ASSERT(result.valid(), "Could not compile lua script");
    }

    std::string lua_script::get_code() const
    {
        return code;
    }

    void lua_script::set_code(const std::string& code, bool recompile)
    {
        this->code = code;
        if (recompile)
        {
            // TODO - Reset state?
            compile();
        }
    }

    const char* lua_script::extension()
    {
        return ".lua";
    }
}
