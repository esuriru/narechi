#pragma once

#include <core/core.hpp>
#include <core/window.hpp>

namespace narechi
{
    // class app : public utils::singleton<app>
    class app
    {
    public:
        explicit app();
        virtual ~app() {}

        void run();
        app& get();
    
    private:
        uptr<window> window;
        bool is_running;

    };

    app* create_app();
}