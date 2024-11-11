#include "asset/sprite_asset.hpp"

#include "graphics/sprite.hpp"

namespace narechi::asset
{
    sprite_asset::sprite_asset(
        const std::filesystem::path& path, graphics::sprite* owner)
        : asset(path.parent_path() / (path.stem().string() + ".nrcsprite"))
        , owner(owner)
    {
        if (!owner)
        {
            is_owning = true;
        }
        texture = graphics::texture2d::load(path, {});
    }

    sptr<graphics::texture2d> sprite_asset::get_texture() const
    {
        return texture;
    }

    sptr<sprite_asset> sprite_asset::create(const std::filesystem::path& path)
    {
        sptr<sprite_asset> new_asset = make_sptr<sprite_asset>(path, nullptr);
        new_asset->write();
        return new_asset;
    }

    sptr<sprite_asset> sprite_asset::load_data(
        const std::filesystem::path& path)
    {
        sptr<sprite_asset> existing_asset
            = make_sptr<sprite_asset>(path, nullptr);
        existing_asset->is_owning = true;
        existing_asset->load();
        return existing_asset;
    }

    void sprite_asset::serialize()
    {
    }

    void sprite_asset::deserialize()
    {
        // TODO - For later
    }
}