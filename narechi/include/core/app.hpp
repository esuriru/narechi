#pragma once

#include "core/core.hpp"
#include "core/window.hpp"
#include "core/layer_stack.hpp"

#include "graphics/graphics_context.hpp"
#include "imgui/imgui_context.hpp"
#include "file/nfd_context.hpp"
#include "asset/database.hpp"

#include <utility>
#include <queue>

namespace narechi
{
    class NRC_API app
    {
    public:
        explicit app();
        virtual ~app() = default;

        static app& get();

        void init_contexts();
        void run();
        void flush_layer_change_queue();

        window& get_window();
        graphics::graphics_context& get_graphics_context();
        imgui_context& get_imgui_context();
        file::nfd_context& get_nfd_context();
        asset::database& get_asset_database();

    protected:
        template<typename T, typename... Args>
        sptr<T> create_and_push_layer(Args&&... args)
        {
            sptr<T> layer = make_sptr<T>(std::forward<Args>(args)...);
            push_layer(layer);
            return layer;
        }

        void push_layer(sptr<layer> layer);
        void push_overlay(sptr<layer> overlay);

        void pop_layer(sptr<layer> layer);
        void pop_overlay(sptr<layer> overlay);

    private:
        enum class layer_change_queue_command
        {
            push_l,
            push_o,
            pop_l,
            pop_o
        };

        void on_event(event& event);

        static app* app_instance;

        std::queue<std::pair<sptr<layer>, layer_change_queue_command>>
            layer_change_queue;

        uptr<window> window;
        uptr<graphics::graphics_context> gfx_ctx;
        uptr<imgui_context> imgui_ctx;
        uptr<file::nfd_context> nfd_ctx;
        asset::database asset_database;

        layer_stack layer_stack;

        bool is_running;
        bool is_minimized;

        bool in_layer_loop_scope;

        float last_frame_time;
    };

    app* create_app();
}
