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
        flecs::cursor cursor = get_cursor();
        reach_depth(cursor);
        return cursor.get_float();
    }

    void raw_component_view::set_float(float value)
    {
        flecs::cursor cursor = get_cursor();
        reach_depth(cursor);
        cursor.set_float(static_cast<double>(value));
    }

    glm::vec2 raw_component_view::get_vec2()
    {
        glm::vec2 return_value;

        flecs::cursor cursor = get_cursor();
        reach_depth(cursor);
        return_value.x = cursor.get_float();
        cursor.next();
        return_value.y = cursor.get_float();
        return return_value;
    }

    void raw_component_view::set_vec2(glm::vec2 vec)
    {
        flecs::cursor cursor = get_cursor();
        reach_depth(cursor);
        cursor.set_float(static_cast<float>(vec.x));
        cursor.next();
        cursor.set_float(static_cast<float>(vec.y));
    }

    flecs::cursor raw_component_view::get_cursor()
    {
        return world.cursor(component_entity, raw_component);
    }

    void raw_component_view::reach_depth(flecs::cursor& cursor)
    {
        for (uint32_t i = 0; i < depth; ++i)
        {
            cursor.push();
        }
    }

    void raw_component_view::set_depth(uint32_t depth)
    {
        this->depth = depth;
    }

}
