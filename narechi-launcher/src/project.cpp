#include "project.hpp"

#include "yaml-cpp/yaml.h"

#include "core/assert.hpp"

#include <fstream>

namespace narechi::editor
{
    project::project(const std::filesystem::path& path)
        : asset(path, props)
    {
    }

    uptr<project> project::load(const std::filesystem::path& path)
    {
        uptr<project> existing_project = make_uptr<project>(path);
        existing_project->asset.load();
        return std::move(existing_project);
    }

    uptr<project> project::create(
        const std::filesystem::path& path, project_properties&& props)
    {
        uptr<project> new_project = make_uptr<project>(path);
        new_project->props = std::move(props);
        new_project->asset.write();
        return std::move(new_project);
    }

    const project_properties& project::get_props() const
    {
        return props;
    }

    const std::filesystem::path& project::get_path() const
    {
        return asset.get_path();
    }
}
