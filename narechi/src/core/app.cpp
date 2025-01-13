#include "core/app.hpp"

#include "core/assert.hpp"
#include "core/events/app_event.hpp"
#include "core/logger.hpp"

#include "file/nfd_context.hpp"
#include "graphics/render_command.hpp"

#include "utils/time_utils.hpp"

extern narechi::file::nfd_context* get_nfd_ctx()
{
    return &(narechi::app::get().get_nfd_context());
}

namespace narechi
{
    app* app::app_instance = nullptr;

    app::app()
        : is_running(true)
        , last_frame_time(0.0f)
        , in_layer_loop_scope(false)
    {
        NRC_ASSERT(app_instance == nullptr,
            "An instance of app has already been created");
        app_instance = this;

        window = window::create({ "narechi window", 1280, 720 });
        window->set_event_callback(NRC_BIND_FN(on_event));

        init_contexts();

        // layer_stack.push_overlay(new imgui_layer(get_imgui_context()));

        graphics::render_command::init();
    }

    void app::init_contexts()
    {
        // The app should own the graphics context
        gfx_ctx = graphics::graphics_context::create(this);
        gfx_ctx->init();

        imgui_ctx = make_uptr<imgui_context>();
        imgui_ctx->init();

        nfd_ctx = make_uptr<file::nfd_context>();
        nfd_ctx->init();

        sol2_ctx = make_uptr<script::sol2_context>();
    }

    void app::run()
    {
        using graphics::render_command;

        while (is_running)
        {
            float current_time = utils::get_time();
            float step = current_time - last_frame_time;
            last_frame_time = current_time;

            render_command::clear_color(glm::vec4(0.32f, 0.32f, 0.32f, 1.0f));

            imgui_ctx->new_frame();

            in_layer_loop_scope = true;

            for (auto& layer : layer_stack)
            {
                layer->on_gui_update();
            }

            in_layer_loop_scope = false;

            imgui_ctx->render();

            in_layer_loop_scope = true;

            for (auto& layer : layer_stack)
            {
                layer->on_update(step);
            }

            in_layer_loop_scope = false;

            window->update();
            gfx_ctx->swap_buffers();

            // Clear layer changes
            flush_layer_change_queue();
        }

        render_command::cleanup();
    }

    void app::flush_layer_change_queue()
    {
        while (!layer_change_queue.empty())
        {
            auto layer_change_pair = layer_change_queue.front();
            auto layer_to_transition = layer_change_pair.first;
            auto current_layer_change_command = layer_change_pair.second;

            switch (current_layer_change_command)
            {
            case layer_change_queue_command::push_l:
                layer_stack.push_layer(layer_to_transition);
                break;
            case layer_change_queue_command::push_o:
                layer_stack.push_overlay(layer_to_transition);
                break;
            case layer_change_queue_command::pop_l:
                layer_stack.pop_layer(layer_to_transition);
                break;
            case layer_change_queue_command::pop_o:
                layer_stack.pop_overlay(layer_to_transition);
                break;
            }

            layer_change_queue.pop();
        }
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

    graphics::graphics_context& app::get_graphics_context()
    {
        NRC_ASSERT(window, "graphics context is not created yet");
        return *gfx_ctx;
    }

    imgui_context& app::get_imgui_context()
    {
        NRC_ASSERT(imgui_ctx, "ImGui context is not created yet");
        return *imgui_ctx;
    }

    file::nfd_context& app::get_nfd_context()
    {
        NRC_ASSERT(nfd_ctx, "NFDe context is not created yet");
        return *nfd_ctx;
    }

    asset::database& app::get_asset_database()
    {
        return asset_database;
    }

    void app::push_layer(sptr<layer> layer)
    {
        if (in_layer_loop_scope)
        {
            layer_change_queue.push(
                std::make_pair(layer, layer_change_queue_command::push_l));
        }
        else
        {
            layer_stack.push_layer(layer);
        }
    }

    void app::push_overlay(sptr<layer> overlay)
    {
        if (in_layer_loop_scope)
        {
            layer_change_queue.push(
                std::make_pair(overlay, layer_change_queue_command::push_o));
        }
        else
        {
            layer_stack.push_overlay(overlay);
        }
    }

    void app::pop_layer(sptr<layer> layer)
    {
        if (in_layer_loop_scope)
        {
            layer_change_queue.push(
                std::make_pair(layer, layer_change_queue_command::pop_l));
        }
        else
        {
            layer_stack.pop_layer(layer);
        }
    }

    void app::pop_overlay(sptr<layer> overlay)
    {
        if (in_layer_loop_scope)
        {
            layer_change_queue.push(
                std::make_pair(overlay, layer_change_queue_command::pop_o));
        }
        else
        {
            layer_stack.pop_overlay(overlay);
        }
    }

    void app::on_event(event& event)
    {
        event_handler handler(event);

        handler.handle<window_resize_event>(
            [](auto& event)
            {
                graphics::render_command::set_viewport(
                    0, 0, event.get_width(), event.get_height());
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