#pragma once

#include "graphics/framebuffer.hpp"
#include "narechi.hpp"

#include "panels/editor_panel.hpp"

namespace narechi::editor
{
    class scene_view_panel : public editor_panel
    {
    public:
        scene_view_panel(sptr<graphics::framebuffer> framebuffer);

        void render() override;

    private:
        sptr<narechi::gui::window> window;
        sptr<gui::image_element> scene_image;
        sptr<graphics::framebuffer> scene_framebuffer;

        void invalidate_proj_matrix();
    };
}