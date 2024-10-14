#pragma once

#include "core/layer.hpp"

#include "imgui/imgui_context.hpp"

namespace narechi
{
    class imgui_layer : public layer
    {
    public:
        imgui_layer(imgui_context& context);
        ~imgui_layer() = default;

        void on_attach() override;
        void on_detach() override;

        void on_update(float dt) override;
        void on_event(event& event) override;
    private:
        imgui_context& context;
    };
}