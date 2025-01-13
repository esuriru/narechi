#include "script/lua_script.hpp"

#include "core/app.hpp"
#include "core/logger.hpp"

#include <unordered_map>
#include <regex>
#include <algorithm>

namespace narechi::script
{
    using std::string;
    using std::unordered_map;
    using std::vector;

    lua_script::lua_script(const std::string& code)
    {
        // auto& sol2_ctx = app::get().get_sol2_context();
        // auto& lua_state = sol2_ctx.get_lua_state();

        auto map = get_function_argument_map(code);

        for (auto& kv_pair : map)
        {
            NRC_CORE_LOG("Function: ", kv_pair.first);
            NRC_CORE_LOG("Arguments: ");
            for (auto& arg : kv_pair.second)
            {
                NRC_CORE_LOG(arg);
            }
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
