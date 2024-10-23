#pragma once

#include "core/core.hpp"
#include "element.hpp"

#include <string>

namespace narechi::gui
{
    struct text_input_element_properties
    {
        float width = 100.0f;
        bool label_on_left = true;
        float label_gap = 0.0f;
        std::string label;
        std::string text;
    };

    class NRC_API text_input_element : public element
    {
    public:
        static sptr<text_input_element> create(
            const text_input_element_properties& props);

        std::string get_text() const;
        virtual void set_text(const std::string& text);

        virtual float get_label_length();
        text_input_element_properties& get_props();

    protected:
        text_input_element(const text_input_element_properties& props);

        text_input_element_properties props;
    };
}