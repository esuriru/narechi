#include "editor_layer.hpp"

#include <core/logger.hpp>

namespace narechi::editor
{
    editor_layer::editor_layer() : layer("EditorLayer") {}

    void editor_layer::on_update(float dt)
    {
        // NRC_CORE_LOG("Timestep: ", dt);
    }

}