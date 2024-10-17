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

    project::project(const std::filesystem::path& path, const std::string& data)
        : props{}
        , asset(path, data, props)
    {
    }

    uptr<project> project::load(const std::filesystem::path& path)
    {
        std::ifstream file_in(path);
        std::ostringstream buffer;
        buffer << file_in.rdbuf();

        return make_uptr<project>(path, buffer.str());
    }

    void project::serialize_and_write() 
    {
        asset.serialize();    
        asset.write();
    }

    const project_properties& project::get_props()
    {
        return props;
    }
}
