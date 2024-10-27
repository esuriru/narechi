#pragma once

#include "gui/button_element.hpp"
#include "narechi.hpp"

#include "panels/editor_panel.hpp"

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
        sptr<narechi::gui::window> window;
        sptr<narechi::gui::button_element> back_button;
        sptr<narechi::gui::button_element> browser_element;

        std::filesystem::path editor_asset_dir;
        std::filesystem::path current_dir;
    };
}