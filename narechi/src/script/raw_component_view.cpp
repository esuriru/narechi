#include "script/raw_component_view.hpp"

#include "core/assert.hpp"

namespace narechi::script
{
    raw_component_view::raw_component_view(flecs::world world,
        flecs::entity_view component_entity, void* component)
        : world(world)
        , component_entity(component_entity)
        , raw_component(component)
    {
        NRC_ASSERT(
            component, "`raw_component_view` created with null component")
    }

    float raw_component_view::get_float()
    {
        flecs::cursor cursor = world.cursor(component_entity, raw_component);
        cursor.push();
        return cursor.get_float();
    }

    void raw_component_view::set_float(float value)
    {
        flecs::cursor cursor = world.cursor(component_entity, raw_component);
        cursor.push();
        cursor.set_float(static_cast<double>(value));
    }

    float raw_component_view::get_float_depth(uint32_t depth)
    {
        flecs::cursor cursor = world.cursor(component_entity, raw_component);
        for (uint32_t i = 0; i < depth; ++i)
        {
            cursor.push();
        }
        return cursor.get_float();
    }

    void raw_component_view::set_float_depth(uint32_t depth, float value)
    {
        flecs::cursor cursor = world.cursor(component_entity, raw_component);
        for (uint32_t i = 0; i < depth; ++i)
        {
            cursor.push();
        }
        cursor.set_float(value);
    }

}
