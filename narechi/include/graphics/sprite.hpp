#pragma once

#include "asset/sprite_asset.hpp"
#include "graphics/texture2d.hpp"
#include "core/core.hpp"

namespace narechi::graphics
{
    class sprite
    {
    public:
        void set_texture(sptr<texture2d> texture);
        sptr<texture2d> get_texture() const;

    private:
        friend class asset::sprite_asset;

        uptr<asset::sprite_asset> asset;
        sptr<texture2d> texture;

        bool flip_vertically;
    };
}