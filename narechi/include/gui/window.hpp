#pragma once

#include "core/core.hpp"
#include "gui/element.hpp"
#include "gui/text_input_element.hpp"
#include "utils/enum_flag_utils.hpp"

#include <string>
#include <functional>

namespace narechi::gui
{
    enum class window_flags
    {
        align_text_elements = 1 << 0,
        no_padding = 1 << 2,
        no_vertical_scrollbar = 1 << 3,
    };

    NRC_ENUM_FLAG_OPERATORS(window_flags);

    struct window_properties
    {
        std::string name;
        bool no_init = false;
        uint32_t width = 0, height = 0;

        uint32_t start_position_x = 0, start_position_y = 0;
        window_flags flags {};

        static bool verify(const window_properties& props);
    };

    class NRC_API window
    {
    public:
        virtual void render() = 0;
        virtual void render(
            const std::function<void()>& render_pipeline_callback);

        static uptr<window> create(const window_properties& props);

        // TODO - Maybe a base check on element class? Implement NVI
        virtual void add_element(sptr<element> element) = 0;
        virtual void add_element(sptr<text_input_element> element) = 0;

        void set_width_height(uint32_t width, uint32_t height);
        void set_default_render_active(bool active);

        void set_active(bool active);
        void set_enable_toggle(bool enable_toggle);

        uint32_t get_width();
        uint32_t get_height();

    protected:
        window(const window_properties& props);

        virtual void set_width_height_impl(uint32_t width, uint32_t height) = 0;

        window_properties props;

        bool has_rendered = false;
        bool default_render_active = true;
        bool active = true;
        bool enable_toggle = false;
    };
}