#include "imgui/imgui_layer.hpp"

#include "imgui/imgui_context.hpp"

namespace narechi
{
    imgui_layer::imgui_layer(imgui_context& context)
        : layer("ImGuiLayer"), context(context)
    {
    }

    void imgui_layer::on_attach() {}

    void imgui_layer::on_detach() {}

    void imgui_layer::on_update(float dt)
    {
        context.new_frame();
        context.render();
    }

    void imgui_layer::on_event(event& event) {}
}