#pragma once

#include "core/core.hpp"

#include "yaml-cpp/node/node.h"

#include <filesystem>

namespace narechi::asset
{
    class NRC_API asset
    {
    public:
        // Ctor for existing assets
        asset(const std::filesystem::path& path, const std::string& data);

        // Ctor for new assets
        asset(std::filesystem::path&& path);

        const std::filesystem::path& get_path();

        virtual void load(const std::string& data);
        virtual void serialize() = 0;
        void write();

    protected:
        YAML::Node node;
        std::filesystem::path path;
    };
}