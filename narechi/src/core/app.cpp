#include "app.hpp"

#include "core/assert.hpp"

namespace narechi
{
    app* app::app_instance = nullptr;

    app::app()
        : is_running(true)
    {
        NRC_ASSERT(app_instance == nullptr, 
            "An instance of app has already been created");
        app_instance = this;

        window = window::create({"narechi window", 1280, 720});
    }

    void app::run()
    {
        while (is_running)
        {
        }
    }

    app& app::get()
    {
        return *app_instance;
    }

    void app::push_layer(layer* layer)
    {
        layer_stack.push_layer(layer);
    }

    void app::push_overlay(layer* overlay)
    {
        layer_stack.push_overlay(overlay);
    }
}