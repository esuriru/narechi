#pragma once

#include "narechi.hpp"
#include "panels/editor_panel.hpp"
#include "asset/component_def_asset.hpp"

namespace narechi::editor
{
    class build_panel : public editor_panel
    {
    public:
        build_panel();

        void render() override;
        void set_export_scene(sptr<scene::scene> scene);
        void set_cdef_asset(sptr<asset::component_def_asset> asset);

        sptr<gui::window> get_window() const;

    private:
        sptr<scene::scene> export_scene;
        sptr<asset::component_def_asset> cdef_asset;

        sptr<gui::window> window;

        sptr<gui::text_input_element> build_directory_input;
        sptr<gui::button_element> build_directory_button;
    };
}