#include "asset/asset.hpp"

#include "core/assert.hpp"
#include "YAML-cpp/yaml.h"
#include "uuid.h"

#include <fstream>

namespace narechi::asset
{
    asset::asset(const std::filesystem::path& path)
        : path(path)
        , is_owning(false)
    {
        // TODO - Utils function
        guid = uuids::to_string(uuids::uuid_system_generator {}());
    }

    const std::filesystem::path& asset::get_path() const
    {
        return path;
    }

    void asset::load(bool deserialize_only)
    {
        if (!deserialize_only)
        {
            std::ifstream file_in(path);
            std::ostringstream buffer;
            buffer << file_in.rdbuf();

            node = YAML::Load(buffer.str());
        }

        deserialize_guid_yaml();
        deserialize();
    }

    void asset::write()
    {
        write(path);
    }

    void asset::write(const std::filesystem::path& path)
    {
        serialize_guid_yaml();
        serialize();

        YAML::Emitter emitter;
        emitter << node;

        std::ofstream file_out(path);
        NRC_ASSERT(file_out.is_open(), "Asset directory is not valid");
        file_out << emitter.c_str();
    }

    void asset::serialize_guid_yaml()
    {
        node["ID"] = guid;
    }

    void asset::deserialize_guid_yaml()
    {
        guid = node["ID"].as<std::string>();
    }

    std::string asset::get_guid() const
    {
        return guid;
    }
}
