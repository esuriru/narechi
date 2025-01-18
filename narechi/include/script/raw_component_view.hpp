#pragma once

#include "flecs.h"
#include "glm/glm.hpp"

namespace narechi::script
{
    // To be created to pass into a script after an .ensure()
    class raw_component_view
    {
    public:
        raw_component_view(flecs::world world,
            flecs::entity_view component_entity, void* component);

        void set_depth(uint32_t depth);

        float get_float();
        void set_float(float value);

        glm::vec2 get_vec2();
        void set_vec2(glm::vec2 vec);

    private:
        flecs::world world;
        flecs::entity_view component_entity;

        void* raw_component;
        uint32_t depth = 1;

        flecs::cursor get_cursor();

        void reach_depth(flecs::cursor& cursor);
    };
}