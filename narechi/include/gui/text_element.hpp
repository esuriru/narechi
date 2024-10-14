#pragma once

#include "core/core.hpp"
#include "element.hpp"

#include <string>

namespace narechi::gui
{
    struct text_element_properties
    {
        std::string text;
    };

    class NRC_API text_element : public element
    {
    public:
        static sptr<text_element> create(const text_element_properties& props);

    protected:
        text_element(const text_element_properties& props);

        std::string text;
    };
}