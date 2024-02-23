#pragma once

#include <utils/singleton.hpp>

namespace narechi
{
    class app final : public utils::singleton<app>
    {
    public:
        explicit app();

        void run();
    
    private:
        bool is_running;


    };

    extern app* create_app();
}