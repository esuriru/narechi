#pragma once

#include "core/core.hpp"

#include "yaml-cpp/node/node.h"

#include <filesystem>

namespace narechi::asset
{
    class NRC_API asset
    {
    public:
        asset(const std::filesystem::path& path);

        const std::filesystem::path& get_path() const;

        void load();
        void write();

    protected:
        std::string data;
        std::filesystem::path path;

    private:
        virtual void serialize() = 0;
        virtual void deserialize() = 0;
    };
}