#include "gui/image_button_element.hpp"

#include "imgui/imgui_image_button_element.hpp"

namespace narechi::gui
{
    sptr<image_button_element> image_button_element::create(
        const button_element_properties& props,
        sptr<graphics::texture2d> texture)
    {
        // For now there is only ImGui
        return make_sptr<imgui_image_button_element>(props, texture);
    }

    void image_button_element::set_texture(sptr<graphics::texture2d> texture)
    {
        this->texture = texture;
    }

    image_button_element::image_button_element(
        sptr<graphics::texture2d> texture)
        : texture(texture)
    {
    }
}