#pragma once

#include "narechi.hpp"

#include "panels/editor_panel.hpp"
#include "graphics/texture2d.hpp"
#include "gui/scope/table_scope.hpp"

#include <filesystem>

namespace narechi::editor
{
    class content_browser_panel : public editor_panel
    {
    public:
        content_browser_panel();

        void render() override;
        void set_editor_asset_dir(
            const std::filesystem::path& path, bool set_current_dir);

    private:
        float browser_element_size = 96.0f;
        float browser_element_padding = 48.0f;

        sptr<narechi::gui::window> window;
        sptr<narechi::gui::button_element> back_button;
        sptr<narechi::gui::image_button_element> browser_element;
        sptr<narechi::gui::text_element> browser_text_element;

        sptr<graphics::texture2d> file_icon_texture;
        sptr<graphics::texture2d> folder_icon_texture;

        std::filesystem::path editor_asset_dir;
        std::filesystem::path current_dir;

        narechi::gui::scope::table_scope_properties browser_table_props {};
    };
}