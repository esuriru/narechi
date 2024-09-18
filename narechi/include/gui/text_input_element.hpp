#pragma once

#include "core/core.hpp"
#include "element.hpp"

#include <string>

namespace narechi::gui
{
    struct text_input_element_properties
    {
        float width = 100;
        bool label_on_left = true;
        std::string label;
        std::string text;
    };

    class NRC_API text_input_element : public element
    {
    public:
        static sptr<text_input_element> create(
            const text_input_element_properties& props);

    protected:
        text_input_element(const text_input_element_properties& props);

        text_input_element_properties props;
    };
}