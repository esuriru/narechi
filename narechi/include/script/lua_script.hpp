#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

#include "flecs.h"
#include "script/sol2_context.hpp"

NRC_FORWARD_DECL_CLASS(narechi::asset, lua_script_meta_asset);

namespace narechi::script
{
    struct NRC_API lua_script_deps
    {
        flecs::world world;
        sol2_context& ctx;
    };

    class NRC_API lua_script
    {
    public:
        lua_script(const lua_script_deps& deps, const std::string& code);
        ~lua_script();

        // static sptr<lua_script> load_new_meta_s(const lua_script_deps& deps,
        //     const std::filesystem::path& code_path);

        void call();
        void compile();

        std::string get_code() const;
        void set_code(const std::string& code, bool recompile);

        static const char* extension();

    private:
        friend class asset::lua_script_meta_asset;
        sptr<asset::lua_script_meta_asset> asset;

        lua_script_deps deps;
        std::string code;

        std::unordered_map<std::string, std::vector<flecs::entity>>
            component_map;
        flecs::query<> query;

        std::unordered_map<std::string, std::vector<std::string>>
        get_function_argument_map(const std::string& code);
    };
}