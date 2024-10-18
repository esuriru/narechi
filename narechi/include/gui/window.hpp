#pragma once

#include "core/core.hpp"
#include "gui/element.hpp"
#include "gui/text_input_element.hpp"
#include "utils/enum_flag_utils.hpp"

#include <string>

namespace narechi::gui
{
    enum class window_flags
    {
        align_text_elements = 1 << 0,
    };

    ENUM_FLAG_OPERATORS(window_flags);

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

        static uptr<window> create(const window_properties& props);

        // TODO - Maybe a base check on element class? Implement NVI
        virtual void add_element(sptr<element> element) = 0;
        virtual void add_element(sptr<text_input_element> element) = 0;

        void set_width_height(uint32_t width, uint32_t height);

        uint32_t get_width();
        uint32_t get_height();

    protected:
        window(const window_properties& props);

        virtual void set_width_height_impl(uint32_t width, uint32_t height) = 0;

        window_properties props;

        bool has_rendered = false;
    };
}