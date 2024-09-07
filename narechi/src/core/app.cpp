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

        init_contexts();

        // layer_stack.push_overlay(new imgui_layer(get_imgui_context()));

        render_command::init();
    }

    void app::init_contexts()
    {
        // The app should own the graphics context
        gfx_ctx = graphics_context::create(this);
        gfx_ctx->init();

        imgui_ctx = make_uptr<imgui_context>();
        imgui_ctx->init();
    }

    void app::run()
    {
        while (is_running)
        {
            float current_time = utils::get_time();
            float step = current_time - last_frame_time;
            last_frame_time = current_time;

            render_command::clear_color(glm::vec4(0.32f, 0.32f, 0.32f, 1.0f));

            imgui_ctx->new_frame();

            for (auto& layer : layer_stack)
            {
                layer->on_gui_update();
            }

            imgui_ctx->render();

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
        NRC_ASSERT(window, "window is not created yet");
        return *window;
    }

    graphics_context& app::get_graphics_context()
    {
        NRC_ASSERT(window, "graphics context is not created yet");
        return *gfx_ctx;
    }

    imgui_context& app::get_imgui_context()
    {
        NRC_ASSERT(window, "ImGui context is not created yet");
        return *imgui_ctx;
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
                return false;
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