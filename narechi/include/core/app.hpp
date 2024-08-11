#pragma once

#include "core/core.hpp"
#include "core/window.hpp"
#include "core/layer_stack.hpp"

#include "rendering/graphics_context.hpp"

namespace narechi
{
    class NRC_API app
    {
    public:
        explicit app();
        virtual ~app() = default;

        static app& get();

        void run();
        window& get_window();
        graphics_context& get_graphics_context();

    protected:
        void push_layer(layer* layer);
        void push_overlay(layer* overlay);

    private:
        void on_event(event& event);

        static app* app_instance;

        uptr<window> window;
        uptr<graphics_context> gfx_ctx;
        layer_stack layer_stack;

        bool is_running;
        bool is_minimized;

        float last_frame_time;
    };

    app* create_app();
}
