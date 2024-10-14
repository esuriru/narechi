#include "project.hpp"

#include "yaml-cpp/emitter.h"

#include "core/assert.hpp"

#include <fstream>

namespace narechi::editor
{
    void project::serialize(
        const std::filesystem::path& output_path, const project& project)
    {
        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Project Name" << YAML::Value
            << project.name;
        emitter << YAML::EndMap;

        std::ofstream file_out(output_path);
        NRC_ASSERT(
            file_out.is_open(), "Project directory is not valid");
        file_out << emitter.c_str();
    }

    project::project(const project_properties& props)
        : name(props.name) 
    {
    
    }
}
