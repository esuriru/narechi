#include "project.hpp"

#include "yaml-cpp/yaml.h" 

#include "core/assert.hpp"

#include <fstream>

namespace narechi::editor
{
    project::project(std::filesystem::path&& path, const project_properties& props)
        : props(props) 
        , asset(std::move(path), this->props)
    {

    }

    void project::serialize_and_write() 
    {
        asset.serialize();    
        asset.write();
    }
}
