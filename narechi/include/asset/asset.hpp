#pragma once

#include "core/core.hpp"

#include <filesystem>

namespace narechi::asset
{
    class NRC_API asset
    {
    public:
        asset(std::filesystem::path&& path);

        const std::filesystem::path& get_path();

    protected:
        std::filesystem::path path;
    };
}