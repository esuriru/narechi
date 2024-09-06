#pragma once

#include "core/layer.hpp"

#include "panels/editor_panel.hpp"

// TODO - Will there be a need to separate the editor from the editor_layer?
namespace narechi::editor
{
    class editor_layer final : public layer
    {
    public:
        explicit editor_layer();

        void on_attach() override;
        void on_detach() override;

        void on_gui_update() override;
        void on_update(float dt) override;

    private:
        std::vector<editor_panel*> panels;
    };
}