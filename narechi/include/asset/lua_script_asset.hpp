#pragma once

#include "asset/asset.hpp"

namespace narechi::asset
{
    class NRC_API lua_script_asset : public asset
    {
    public:
        lua_script_asset(const std::filesystem::path& path);

        static sptr<lua_script_asset> load(
            const std::filesystem::path& code_path);

        std::string get_code() const;

    private:
        void serialize() override;
        void deserialize() override;
    };
}