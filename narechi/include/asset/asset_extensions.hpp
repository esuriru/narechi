#pragma once

#include "asset/asset_extensions.hpp"
#include "asset/scene_asset.hpp"
#include "asset/sprite_asset.hpp"
#include "core/core.hpp"

#include <string>
#include <unordered_map>
#include <functional>

namespace narechi::asset
{
    template<typename T>
    struct extension;

    template<>
    struct extension<narechi::asset::sprite_asset>
    {
        static constexpr const char* value = ".nrcsprite";
    };

    template<>
    struct extension<narechi::asset::scene_asset>
    {
        static constexpr const char* value = ".nrcscene";
    };
}