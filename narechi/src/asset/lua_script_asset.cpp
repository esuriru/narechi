#include "asset/lua_script_asset.hpp"

namespace narechi::asset
{
    lua_script_asset::lua_script_asset(const std::filesystem::path& path)
        : asset(path, get_guid(), false)
    {
    }

    sptr<lua_script_asset> lua_script_asset::load(
        const std::filesystem::path& code_path)
    {
        sptr<lua_script_asset> existing_asset
            = make_sptr<lua_script_asset>(code_path);
        existing_asset->asset::load();
        return existing_asset;
    }

    std::string lua_script_asset::get_code() const
    {
        return this->data;
    }

    void lua_script_asset::serialize()
    {
    }

    void lua_script_asset::deserialize()
    {
    }
}