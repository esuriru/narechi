#include "asset/asset.hpp"

#include "core/assert.hpp"
#include "YAML-cpp/yaml.h"
#include "uuid.h"

#include <fstream>

namespace narechi::asset
{
    asset::asset(const std::filesystem::path& path,
        const std::string& custom_guid, bool is_yaml_asset)
        : path(path)
        , is_owning(false)
        , is_yaml_asset(is_yaml_asset)
    {
        guid = custom_guid.empty() ?
            uuids::to_string(uuids::uuid_system_generator {}()) :
            custom_guid;
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

            if (is_yaml_asset)
            {
                node = YAML::Load(buffer.str());
            }
            else
            {
                data = buffer.str();
            }
        }

        if (is_yaml_asset)
        {
            deserialize_guid_yaml();
        }
        deserialize();
    }

    void asset::write()
    {
        write(path);
    }

    void asset::write(const std::filesystem::path& path)
    {
        if (is_yaml_asset)
        {
            serialize_guid_yaml();
        }

        serialize();

        std::ofstream file_out(path);
        NRC_ASSERT(file_out.is_open(), "Asset directory is not valid");

        if (is_yaml_asset)
        {
            YAML::Emitter emitter;
            emitter << node;
            file_out << emitter.c_str();
        }
        else
        {
            file_out << data;
        }
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
