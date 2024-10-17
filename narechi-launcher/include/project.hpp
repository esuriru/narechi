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
        project(const std::filesystem::path& path, const std::string& data);

        static uptr<project> load(const std::filesystem::path& path);

        void serialize_and_write();

        const project_properties& get_props();
    private:
        project_properties props;
        project_asset asset;
    };
}