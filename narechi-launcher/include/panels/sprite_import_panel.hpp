#pragma once

#include "gui/button_element.hpp"
#include "narechi.hpp"

#include "panels/editor_panel.hpp"

namespace narechi::editor
{
    class sprite_import_panel : public editor_panel
    {
    public:
        sprite_import_panel();

        void render() override;
        void set_editor_asset_dir(const std::filesystem::path& dir);

    private:
        sptr<narechi::gui::window> window;
        sptr<narechi::gui::text_input_element> image_directory_input;
        sptr<gui::button_element> image_select_directory_button;
        sptr<gui::button_element> import_button;

        std::filesystem::path asset_dir;
    };
}