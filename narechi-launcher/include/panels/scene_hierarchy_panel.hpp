#pragma once

#include "narechi.hpp"

#include "panels/editor_panel.hpp"

#include <filesystem>

namespace narechi::editor
{
    class scene_hierarchy_panel : public editor_panel
    {
    public:
        scene_hierarchy_panel();

        void render() override;

    private:
        sptr<narechi::gui::window> window;

        sptr<narechi::scene::scene> current_scene;
    };
}