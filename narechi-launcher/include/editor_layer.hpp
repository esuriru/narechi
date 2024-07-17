#pragma once

#include "core/layer.hpp"

namespace narechi::editor
{
    class editor_layer final : public layer
    {
    public:
        explicit editor_layer();

        virtual void on_update(float dt) override;
    };
}