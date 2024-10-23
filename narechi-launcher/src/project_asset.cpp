#include "project_asset.hpp"
#include "project.hpp"

#include "yaml-cpp/yaml.h"

#include <fstream>

namespace YAML
{
    using narechi::editor::project_properties;

    template<>
    struct convert<project_properties>
    {
        static Node encode(const project_properties& props)
        {
            Node node(NodeType::Map);
            node.force_insert("Name", props.name);

            return node;
        }

        static bool decode(const Node& node, project_properties& props)
        {
            if (!node.IsMap())
            {
                return false;
            }

            props.name = node["Name"].as<std::string>();
            return true;
        }
    };
}

namespace narechi::editor
{
    project_asset::project_asset(
        const std::filesystem::path& path, project_properties& props)
        : asset::asset(path), props(props)
    {
    }

    void project_asset::serialize()
    {
        node = props;
    }

    void project_asset::deserialize()
    {
        props = node.as<project_properties>();
    }
}
