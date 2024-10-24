#include "scene/scene.hpp"

#include "asset/scene_asset.hpp"

namespace narechi::scene
{
    scene::scene(const std::filesystem::path& path)
        : world()
        , asset(make_uptr<asset::scene_asset>(path, *this))
    {
    }

    scene::~scene()
    {
        asset.reset();
        world.release();
    }

    void scene::awake()
    {
        flecs::entity test_entity = world.entity();
    }

    void scene::update(float delta_time)
    {
        world.progress(delta_time);
    }
}