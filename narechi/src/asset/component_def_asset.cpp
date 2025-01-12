#include "asset/component_def_asset.hpp"

namespace narechi::asset
{
    component_def_asset::component_def_asset(const std::filesystem::path& path)
        : asset(path, get_guid(), false)
    {
    }

    sptr<component_def_asset> component_def_asset::load(
        const std::filesystem::path& code_path)
    {
        sptr<component_def_asset> existing_asset
            = make_sptr<component_def_asset>(code_path);
        existing_asset->asset::load();
        return existing_asset;
    }

    std::string component_def_asset::get_guid()
    {
        return "component_def_guid";
    }

    std::string component_def_asset::get_code() const
    {
        return this->data;
    }

    void component_def_asset::serialize()
    {
    }

    void component_def_asset::deserialize()
    {
    }
}