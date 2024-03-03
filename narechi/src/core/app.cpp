#include "app.hpp"

#include "core/assert.hpp"

namespace narechi
{
    static app* app_instance = nullptr;

    app::app()
    {
        NRC_ASSERT(app_instance == nullptr, 
            "An instance of app has already been created");
        app_instance = this;

        window = window::create({"narechi window", 1280, 720});
    }

    void app::run()
    {

    }

    app& app::get()
    {
        return *app_instance;
    }
}