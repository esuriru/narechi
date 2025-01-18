#pragma once

#include "asset/asset.hpp"
#include "script/lua_script.hpp"

namespace narechi::asset
{
    class NRC_API lua_script_meta_asset : public asset
    {
    public:
        lua_script_meta_asset(const std::filesystem::path& path);

        static sptr<lua_script_meta_asset> load_existing_script(
            const script::lua_script_deps& deps,
            const std::filesystem::path& meta_path);
        static sptr<lua_script_meta_asset> create(
            const script::lua_script_deps& deps,
            const std::filesystem::path& meta_path);

        std::string get_code() const;
        void compile();

        sptr<script::lua_script> get_script() const;

    private:
        sptr<script::lua_script> script;
        std::filesystem::path code_path;

        void serialize() override;
        void deserialize() override;
    };
}