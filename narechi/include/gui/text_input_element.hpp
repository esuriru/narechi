#pragma once

#include "core/core.hpp"
#include "element.hpp"

#include <string>

namespace narechi::gui
{
    struct text_input_element_properties
    {
        std::string text;
    };

    class NRC_API text_input_element : public element
    {
    public:
        static sptr<text_input_element> create(
            const text_input_element_properties& props);

    protected:
        text_input_element(const text_input_element_properties& props);

        std::string text;
    };
}