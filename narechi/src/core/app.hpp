#pragma once

#include <core/core.hpp>
#include <core/window.hpp>
#include <core/layer_stack.hpp>

namespace narechi
{
    class NRC_API app
    {
    public:
        explicit app();
        virtual ~app() {}

        void run();
        app& get();
    
    protected:
        void push_layer(layer* layer); 
        void push_overlay(layer* overlay);

    private:
        static app* app_instance;

        uptr<window> window;
        layer_stack layer_stack;

        bool is_running;
        bool is_minimized;

        float last_frame_time;

    };

    app* create_app();
}
