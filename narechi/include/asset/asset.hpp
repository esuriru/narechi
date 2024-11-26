#pragma once

#include "core/core.hpp"
#include "yaml-cpp/yaml.h"

#include <filesystem>

namespace narechi::asset
{
    // NOTE - Will there be a need to have a non-yaml asset?
    class NRC_API asset
    {
    public:
        asset(const std::filesystem::path& path);

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
        bool is_owning;

        std::string guid;

    private:
        virtual void serialize() = 0;
        virtual void deserialize() = 0;
    };
}