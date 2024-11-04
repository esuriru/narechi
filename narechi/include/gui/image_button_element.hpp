#pragma once

#include "graphics/texture2d.hpp"
#include "gui/button_element.hpp"

namespace narechi::gui
{
    class NRC_API image_button_element : public virtual button_element
    {
    public:
        static sptr<image_button_element> create(
            const button_element_properties& props,
            sptr<graphics::texture2d> texture = nullptr);

        void set_texture(sptr<graphics::texture2d> texture);

    protected:
        sptr<graphics::texture2d> texture = nullptr;

        image_button_element() = default;
        image_button_element(sptr<graphics::texture2d> texture);
    };
}
