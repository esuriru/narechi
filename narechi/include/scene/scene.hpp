#pragma once

#include "core/core.hpp"

#include "flecs.h"

#include <filesystem>

NRC_FORWARD_DECL_CLASS(narechi::asset, scene_asset);

namespace narechi::scene
{
    class NRC_API scene
    {
    public:
        scene(const std::string& name, const std::filesystem::path& path);
        ~scene();

        void awake();
        void update(float delta_time);

        void add_entity();

        void save();

    private:
        std::string name;
        flecs::world world;
        uptr<asset::scene_asset> asset;

        friend class asset::scene_asset;
    };
}