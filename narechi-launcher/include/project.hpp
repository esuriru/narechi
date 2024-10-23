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
        project(const std::filesystem::path& path);

        static uptr<project> load(const std::filesystem::path& path);
        static uptr<project> create(
            const std::filesystem::path& path, project_properties&& props);

        const project_properties& get_props() const;

    private:
        project_properties props;
        project_asset asset;
    };
}