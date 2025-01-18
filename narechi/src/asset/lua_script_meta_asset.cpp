#include "asset/lua_script_meta_asset.hpp"
#include "utils/file_utils.hpp"

namespace narechi::asset
{
    lua_script_meta_asset::lua_script_meta_asset(
        const std::filesystem::path& path)
        : asset(path)
    {
    }

    sptr<lua_script_meta_asset> lua_script_meta_asset::load_existing_script(
        const script::lua_script_deps& deps,
        const std::filesystem::path& meta_path)
    {
        sptr<lua_script_meta_asset> existing_asset
            = make_sptr<lua_script_meta_asset>(meta_path);
        existing_asset->asset::load();

        existing_asset->code_path
            = std::filesystem::path(meta_path).replace_extension(
                script::lua_script::extension());
        existing_asset->script = make_sptr<script::lua_script>(
            deps, utils::file::open_file_as_string(existing_asset->code_path));
        existing_asset->is_owning = true;
        return existing_asset;
    }

    sptr<lua_script_meta_asset> lua_script_meta_asset::create(
        const script::lua_script_deps& deps,
        const std::filesystem::path& meta_path)
    {
        sptr<lua_script_meta_asset> new_asset
            = make_sptr<lua_script_meta_asset>(meta_path);
        new_asset->code_path
            = std::filesystem::path(meta_path).replace_extension(".lua");

        new_asset->script = make_sptr<script::lua_script>(
            deps, utils::file::open_file_as_string(new_asset->code_path));
        new_asset->is_owning = true;
        new_asset->write();
        return new_asset;
    }

    std::string lua_script_meta_asset::get_code() const
    {
        return this->data;
    }

    void lua_script_meta_asset::compile()
    {
        script->reset();
        script->set_code(utils::file::open_file_as_string(code_path));
        script->compile();
    }

    sptr<script::lua_script> lua_script_meta_asset::get_script() const
    {
        return script;
    }

    void lua_script_meta_asset::serialize()
    {
    }

    void lua_script_meta_asset::deserialize()
    {
    }
}