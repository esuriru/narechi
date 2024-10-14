#pragma once

#include <filesystem>

namespace narechi::asset
{
    class asset
    {
    public:
        asset(std::filesystem::path&& path);

        const std::filesystem::path& get_path();

    private:
        std::filesystem::path path;
    };
}