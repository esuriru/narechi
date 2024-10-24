#include "project.hpp"

#include "project_asset.hpp"

#include "yaml-cpp/yaml.h"

#include "core/assert.hpp"

#include <fstream>

namespace narechi::editor
{
    project::project(const std::filesystem::path& path)
        : asset(make_uptr<project_asset>(path, data))
    {
    }

    project::~project()
    {
    }

    uptr<project> project::load(const std::filesystem::path& path)
    {
        uptr<project> existing_project = make_uptr<project>(path);
        existing_project->asset->load();
        return std::move(existing_project);
    }

    uptr<project> project::create(
        const std::filesystem::path& path, const std::string& name)
    {
        uptr<project> new_project = make_uptr<project>(path);
        new_project->data.name = name;
        new_project->asset->write();
        return std::move(new_project);
    }

    const project::project_data& project::get_data() const
    {
        return data;
    }

    const std::filesystem::path& project::get_path() const
    {
        return asset->get_path();
    }
}
