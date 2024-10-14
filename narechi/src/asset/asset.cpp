#include "asset/asset.hpp"

namespace narechi::asset
{
    narechi::asset::asset::asset(std::filesystem::path&& path)
        : path(std::move(path))
    {
    }

    const std::filesystem::path& asset::get_path()
    {
        return path;
    }
}
