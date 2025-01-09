#pragma once

#include "core/core.hpp"
#include "element.hpp"

#include <string>

namespace narechi::gui
{
    struct float_input_element_properties
    {
        std::string custom_id {};
        float width = 100.0f;
        bool label_on_left = true;
        float label_gap = 0.0f;
        std::string label {};
        float* value = nullptr;
        bool same_line = false;
    };

    class NRC_API float_input_element : public element
    {
    public:
        static sptr<float_input_element> create(
            const float_input_element_properties& props);

        virtual float get_label_length();
        float_input_element_properties& get_props();

    protected:
        float_input_element(const float_input_element_properties& props);

        float_input_element_properties props;
    };
}