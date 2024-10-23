#include "asset/scene_asset.hpp"

#include "scene/scene.hpp"

#include "flecs.h"

namespace narechi::asset
{
    scene_asset::scene_asset(
        const std::filesystem::path& path, scene::scene& scene)
        : asset(path), scene(scene)
    {
    }

    void scene_asset::serialize()
    {
        data = scene.world.to_json();
    }

    void scene_asset::deserialize()
    {
        scene.world.from_json(data.c_str());
    }
}