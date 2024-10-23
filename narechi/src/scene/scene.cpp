#include "scene/scene.hpp"

namespace narechi::scene
{
    scene::scene()
        : world()
    {
    }

    scene::~scene()
    {
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