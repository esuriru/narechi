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
        float get_float_l(uint32_t length);

        void set_float(float value);
        void set_float_l(uint32_t length, float value);

        glm::vec2 get_vec2();
        glm::vec2 get_vec2_l(uint32_t length);

        void set_vec2(glm::vec2 vec);
        void set_vec2_l(uint32_t length, glm::vec2 vec);

    private:
        flecs::world world;
        flecs::entity_view component_entity;

        void* raw_component;

        uint32_t depth = 1;

        flecs::cursor get_cursor();

        void reach_depth(flecs::cursor& cursor);
        void reach_length(
            flecs::cursor& cursor, uint32_t length, uint32_t component_count);
    };
}