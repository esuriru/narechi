#pragma once

#include "flecs.h"

namespace narechi::script
{
    // To be created to pass into a script after an .ensure()
    class raw_component_view
    {
    public:
        raw_component_view(flecs::world world,
            flecs::entity_view component_entity, void* component);

        float get_float();
        void set_float(float value);

        float get_float_depth(uint32_t depth);

    private:
        flecs::world world;
        flecs::entity_view component_entity;

        void* raw_component;
    };
}