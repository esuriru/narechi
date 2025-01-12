#pragma once

#include "asset/asset.hpp"

namespace narechi::asset
{
    class NRC_API component_def_asset : public asset
    {
    public:
        component_def_asset(const std::filesystem::path& path);

        static sptr<component_def_asset> load(
            const std::filesystem::path& code_path);
        static std::string get_guid();

        std::string get_code() const;

    private:
        void serialize() override;
        void deserialize() override;
    };
}