#include "gui/image_element.hpp"

#include "imgui/imgui_image_element.hpp"

namespace narechi::gui
{
    sptr<image_element> image_element::create(
        const image_element_properties& props)
    {
        // For now there is only ImGui
        return make_sptr<imgui_image_element>(props);
    }

    void image_element::set_texture_gfx_ctx_id(const uint32_t id)
    {
        props.texture_gfx_ctx_id = id;
    }

    void image_element::set_width(const float width)
    {
        props.width = width;
    }

    void image_element::set_height(const float height)
    {
        props.height = height;
    }

    image_element::image_element(const image_element_properties& props)
    {
        // TODO - Verify props
        this->props = props;
    }
}