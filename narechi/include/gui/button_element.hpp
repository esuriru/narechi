#pragma once

#include "core/core.hpp"
#include "element.hpp"

#include <string>
#include <functional>

namespace narechi::gui
{
    struct button_element_properties
    {
        bool same_line = false;
        std::string label;
        std::function<void()> on_click = nullptr;
    };

    class NRC_API button_element : public element
    {
    public:
        static sptr<button_element> create(
            const button_element_properties& props);

    protected:
        button_element(const button_element_properties& props);

        button_element_properties props;
    };
}