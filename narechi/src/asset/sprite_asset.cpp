#include "asset/sprite_asset.hpp"

#include "graphics/sprite.hpp"

namespace narechi::asset
{
    sprite_asset::sprite_asset(
        const std::filesystem::path& path, graphics::sprite* owner)
        : asset(path)
        , owner(owner)
    {
    }

    void sprite_asset::serialize()
    {
    }

    void sprite_asset::deserialize()
    {
        // TODO - For later
    }
}