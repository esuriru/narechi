#include "app.hpp"

namespace narechi
{
    static app* app_instance = nullptr;

    app::app()
    {
        app_instance = this;
    }

    void app::run()
    {

    }
}