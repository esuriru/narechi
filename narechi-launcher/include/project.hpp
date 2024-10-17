#pragma once

#include "project_asset.hpp"

#include <string>
#include <filesystem>

namespace narechi::editor
{
    struct project_properties
    {
        std::string name;
    };

    class project
    {
    public:
        project(std::filesystem::path&& output_path,
            const project_properties& props);

        void serialize_and_write();

    private:
        project_properties props;
        project_asset asset;
    };
}