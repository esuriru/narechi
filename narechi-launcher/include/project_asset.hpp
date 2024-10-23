#pragma once

#include <core/core.hpp>

#include "narechi.hpp"

#include <filesystem>

namespace narechi::editor
{
    struct project_properties;

    class project_asset : public asset::asset
    {
    public:
        project_asset(
            const std::filesystem::path& path, project_properties& props);

    private:
        YAML::Node node;
        project_properties& props;

        void serialize() override;
        void deserialize() override;
    };
}