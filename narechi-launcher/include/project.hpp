#pragma once

#include "core/core.hpp"

#include <string>
#include <filesystem>

namespace narechi::editor
{
    class project_asset;

    class project
    {
    public:
        struct project_data
        {
            std::string name;
            std::string startup_scene_name;
        };

        project(const std::filesystem::path& path);
        ~project();

        static uptr<project> load(const std::filesystem::path& path);
        static uptr<project> create(
            const std::filesystem::path& path, const std::string& name);

        void set_startup_scene_name(const std::string& scene_name);
        void save();

        const project_data& get_data() const;
        const std::filesystem::path& get_path() const;

    private:
        project_data data;
        uptr<project_asset> asset;
    };
}