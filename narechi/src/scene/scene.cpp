#include "scene/scene.hpp"

#include "asset/scene_asset.hpp"

namespace narechi::scene
{
    scene::scene(const std::string& name, const std::filesystem::path& path)
        : name(name)
        , world()
        , asset(make_uptr<asset::scene_asset>(path, *this))
    {
        asset->write();
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

    void scene::add_entity()
    {
        world.entity();
    }

    void scene::save()
    {
        asset->write();
    }
}