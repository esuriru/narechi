#include "gui/float_input_element.hpp"

#include "imgui/imgui_float_input_element.hpp"

namespace narechi::gui
{
    sptr<float_input_element> float_input_element::create(
        const float_input_element_properties& props)
    {
        // For now there is only ImGui
        return make_sptr<imgui_float_input_element>(props);
    }

    float float_input_element::get_label_length()
    {
        // For GUI libraries that don't have impl this
        return 0.0f;
    }

    float_input_element_properties& float_input_element::get_props()
    {
        return props;
    }

    float_input_element::float_input_element(
        const float_input_element_properties& props)
        : element(static_cast<bool>(props.custom_id.empty()))
        , props(props)
    {
        set_custom_uid(props.custom_id);
        // TODO - Verify props
    }
}