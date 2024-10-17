#include "asset/asset.hpp"

#include "core/assert.hpp"

#include "yaml-cpp/yaml.h"

#include <fstream>

namespace narechi::asset
{
    asset::asset(const std::filesystem::path& path, const std::string& data)
        : path(path)
        , node()
    {
        load(data);
    }

    asset::asset(std::filesystem::path&& path)
        : path(std::move(path))
        , node()
    {
    }

    const std::filesystem::path& asset::get_path()
    {
        return path;
    }

    void asset::load(const std::string& data)
    {
        node = YAML::Load(data);
    }

    void asset::write()
    {
        YAML::Emitter emitter;
        emitter << node; 

        std::ofstream file_out(path); 
        NRC_ASSERT(
            file_out.is_open(), "Asset directory is not valid");
        file_out << emitter.c_str();
    }
}
