#include "asset/asset.hpp"

#include "core/assert.hpp"

#include "yaml-cpp/yaml.h"

#include <fstream>

namespace narechi::asset
{
    asset::asset(const std::filesystem::path& path)
        : path(path)
        , node()
    {
    }

    const std::filesystem::path& asset::get_path()
    {
        return path;
    }

    void asset::load()
    {
        std::ifstream file_in(path);
        std::ostringstream buffer;
        buffer << file_in.rdbuf();

        node = YAML::Load(buffer.str());

        deserialize();
    }

    void asset::write()
    {
        serialize();

        YAML::Emitter emitter;
        emitter << node; 

        std::ofstream file_out(path); 
        NRC_ASSERT(
            file_out.is_open(), "Asset directory is not valid");
        file_out << emitter.c_str();
    }
}
