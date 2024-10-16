#include "project_asset.hpp"
#include "project.hpp"

#include "yaml-cpp/emitter.h"

#include <fstream>

namespace narechi::editor
{
    project_asset::project_asset(
        std::filesystem::path&& path, project_properties& props)
        : asset::asset(std::move(path))
        , props(props)
    {
    }

    void project_asset::serialize() 
    {
        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Project Name" << YAML::Value
            << props.name; 
        emitter << YAML::EndMap;

        std::ofstream file_out(path); 
        NRC_ASSERT(
            file_out.is_open(), "Project directory is not valid");
        file_out << emitter.c_str();
    }
}
        