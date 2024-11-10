#include "project_asset.hpp"
#include "project.hpp"

namespace narechi::editor
{
    project_asset::project_asset(
        const std::filesystem::path& path, project::project_data* data)
        : asset::asset(path)
        , project_data(data)
    {
    }

    project_asset::~project_asset()
    {
    }

    void project_asset::serialize()
    {
        node["Name"] = project_data->name;
        node["Startup Scene Name"] = project_data->startup_scene_name;
        // node = *project_data;
        // YAML::Emitter emitter;
        // emitter << node;

        // data = emitter.c_str();
    }

    void project_asset::deserialize()
    {
        project_data->name = node["Name"].as<std::string>();
        project_data->startup_scene_name
            = node["Startup Scene Name"].as<std::string>();
    }
}
