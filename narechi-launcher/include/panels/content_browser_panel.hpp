#pragma once

#include "gui/button_element.hpp"
#include "narechi.hpp"

#include "panels/editor_panel.hpp"
#include "rendering/texture2d.hpp"

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

        sptr<narechi::gui::window> window;
        sptr<narechi::gui::button_element> back_button;
        sptr<narechi::gui::button_element> browser_element;

        sptr<rendering::texture2d> file_icon_texture;

        std::filesystem::path editor_asset_dir;
        std::filesystem::path current_dir;
    };
}