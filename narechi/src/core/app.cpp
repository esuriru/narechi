#include "core/app.hpp"

#include "core/assert.hpp"
#include "core/events/app_event.hpp"
#include "core/logger.hpp"

#include "rendering/render_command.hpp"

#include "imgui/imgui_layer.hpp"

#include "utils/time_utils.hpp"


namespace narechi
{
    app* app::app_instance = nullptr;

    app::app() : is_running(true), last_frame_time(0.0f)
    {
        NRC_ASSERT(app_instance == nullptr,
            "An instance of app has already been created");
        app_instance = this;

        window = window::create({ "narechi window", 1280, 720 });
        window->set_event_callback(NRC_BIND_FN(on_event));

        // The app should own the graphics context
        gfx_ctx = graphics_context::create(this);
        gfx_ctx->init();

        layer_stack.push_overlay(new imgui_layer());

        render_command::init();
    }

    void app::run()
    {
        while (is_running)
        {
            float current_time = utils::get_time();
            float step = current_time - last_frame_time;
            last_frame_time = current_time;

            render_command::clear_color(glm::vec4(0.32f, 0.32f, 0.32f, 1.0f));

            for (auto& layer : layer_stack)
            {
                layer->on_update(step);
            }

            render_command::draw();

            window->update();
            gfx_ctx->swap_buffers();
        }

        render_command::cleanup();
    }

    app& app::get()
    {
        return *app_instance;
    }

    window& app::get_window()
    {
        return *window;
    }

    graphics_context& app::get_graphics_context()
    {
        return *gfx_ctx;
    }

    void app::push_layer(layer* layer)
    {
        layer_stack.push_layer(layer);
    }

    void app::push_overlay(layer* overlay)
    {
        layer_stack.push_overlay(overlay);
    }

    void app::on_event(event& event)
    {
        event_handler handler(event);

        handler.handle<window_resize_event>(
            [](auto& event)
            {
                NRC_CORE_LOG(event.to_string());
                return true;
            });

        handler.handle<window_close_event>(
            [this](auto& event)
            {
                is_running = false;
                return true;
            });

        for (auto it = layer_stack.rbegin(); it != layer_stack.rend(); ++it)
        {
            if (event.handled)
            {
                break;
            }

            (*it)->on_event(event);
        }
    }
}