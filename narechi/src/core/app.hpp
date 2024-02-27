#pragma once

// #include <utils/singleton.hpp>

namespace narechi
{
    // class app : public utils::singleton<app>
    class app
    {
    public:
        explicit app();

        void run();
    
    private:
        bool is_running;


    };

    extern app* create_app();
}