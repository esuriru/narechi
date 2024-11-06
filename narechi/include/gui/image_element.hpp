#pragma once

#include "core/core.hpp"
#include "element.hpp"

#include "graphics/texture2d.hpp"

namespace narechi::gui
{
    struct image_element_properties
    {
        static constexpr float null_size = 0;

        sptr<graphics::texture2d> texture = nullptr;
        uint32_t texture_gfx_ctx_id = 0;
        float width = null_size;
        float height = null_size;
    };

    class NRC_API image_element : public element
    {
    public:
        static sptr<image_element> create(
            const image_element_properties& props);

        void set_texture_gfx_ctx_id(const uint32_t id);

        void set_width(const float width);
        void set_height(const float height);

    protected:
        image_element(const image_element_properties& props);

        image_element_properties props;
    };
}