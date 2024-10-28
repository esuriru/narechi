#pragma once

#include "core/core.hpp"
#include "element.hpp"

#include <string>
#include <functional>

namespace narechi::gui
{
    struct button_element_properties
    {
        static constexpr float null_size = 0;

        bool same_line = false;
        std::string label;
        std::function<void()> on_click = nullptr;
        float width = null_size;
        float height = null_size;
    };

    class NRC_API button_element : public element
    {
    public:
        static sptr<button_element> create(
            const button_element_properties& props);

        void set_label(const std::string& label);
        void set_on_click_callback(const std::function<void()> callback);
        void set_width(float width);
        void set_height(float height);

        virtual bool is_pressed() const = 0;

    protected:
        button_element(const button_element_properties& props);
        button_element() = default;

        button_element_properties props;
    };
}