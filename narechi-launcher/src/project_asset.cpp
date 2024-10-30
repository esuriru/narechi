#include "project_asset.hpp"
#include "project.hpp"

#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

#include <fstream>

namespace YAML
{
    using narechi::editor::project;

    template<>
    struct convert<project::project_data>
    {
        static Node encode(const project::project_data& data)
        {
            Node node(NodeType::Map);
            node.force_insert("Name", data.name);
            node.force_insert("Startup Scene Name", data.startup_scene_name);

            return node;
        }

        static bool decode(const Node& node, project::project_data& data)
        {
            if (!node.IsMap())
            {
                return false;
            }

            data.name = node["Name"].as<std::string>();
            data.startup_scene_name
                = node["Startup Scene Name"].as<std::string>();
            return true;
        }
    };
}

namespace narechi::editor
{
    project_asset::project_asset(
        const std::filesystem::path& path, project::project_data* data)
        : asset::asset(path)
        , project_data(data)
        , node()
    {
    }

    project_asset::~project_asset()
    {
    }

    void project_asset::serialize()
    {
        node = *project_data;
        YAML::Emitter emitter;
        emitter << node;

        data = emitter.c_str();
    }

    void project_asset::deserialize()
    {
        node = YAML::Load(data);
        *project_data = node.as<project::project_data>();
    }
}
