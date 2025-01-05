#pragma once

#include "flecs.h"

namespace narechi::editor
{
    struct entity_selection_context
    {
        bool active = false;
        flecs::entity selected_entity = flecs::entity::null();
    };
}