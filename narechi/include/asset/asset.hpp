#pragma once

#include "core/core.hpp"
#include "yaml-cpp/yaml.h"

#include <filesystem>

namespace narechi::asset
{
    class NRC_API asset
    {
    public:
        asset(const std::filesystem::path& path,
            const std::string& custom_guid = {}, bool is_yaml_asset = true);

        const std::filesystem::path& get_path() const;

        void load(bool deserialize_only = false);
        void write();
        void write(const std::filesystem::path& path);

        void serialize_guid_yaml();
        void deserialize_guid_yaml();

        std::string get_guid() const;

    protected:
        YAML::Node node;
        std::string data;
        std::filesystem::path path;

        std::string guid;

        bool is_owning;
        bool is_yaml_asset;

    private:
        virtual void serialize() = 0;
        virtual void deserialize() = 0;
    };
}