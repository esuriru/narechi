#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace narechi::script
{
    class lua_script
    {
    public:
        lua_script(const std::string& code);

        std::unordered_map<std::string, std::vector<std::string>>
        get_function_argument_map(const std::string& code);
    };
}