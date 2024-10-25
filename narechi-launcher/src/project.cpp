#include "project.hpp"

#include "project_asset.hpp"

#include "yaml-cpp/yaml.h"

#include "core/assert.hpp"

#include <fstream>

namespace narechi::editor
{
    project::project(const std::filesystem::path& path)
        : asset(make_uptr<project_asset>(path, &data))
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
        new_project->save();
        return std::move(new_project);
    }

    void project::set_startup_scene_name(const std::string& scene_name)
    {
        data.startup_scene_name = scene_name;
    }

    void project::save()
    {
        asset->write();
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
