#pragma once

#include "asset/asset_extensions.hpp"
#include "asset/lua_script_meta_asset.hpp"
#include "asset/scene_asset.hpp"
#include "asset/sprite_asset.hpp"
#include "asset/component_def_asset.hpp"

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

    template<>
    struct extension<narechi::asset::component_def_asset>
    {
        static constexpr const char* value = ".nrccdef";
    };

    template<>
    struct extension<narechi::asset::lua_script_meta_asset>
    {
        static constexpr const char* value = ".nrcluameta";
    };
}