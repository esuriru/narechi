#pragma once

#include <core/core.hpp>
#include <core/window.hpp>

namespace narechi
{
    class NRC_API app
    {
    public:
        explicit app();
        virtual ~app() {}

        void run();
        app& get();
    
    private:
        uptr<window> window;

        bool is_running;
        bool is_minimized;

    };

    app* create_app();
}
