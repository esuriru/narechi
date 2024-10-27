#include "panels/content_browser_panel.hpp"
#include "gui/button_element.hpp"

namespace narechi::editor
{
    content_browser_panel::content_browser_panel()
        : editor_panel("Content Browser")
        , window(gui::window::create({ .name = "Content Browser" }))
    {
        back_button = gui::button_element::create({ .label = "<-",
            .on_click = [this]()
            {
                NRC_ASSERT(!editor_asset_dir.empty(),
                    "Back button pressed when editor asset directory is empty");
                current_dir = current_dir.parent_path();
            } });

        browser_element = gui::button_element::create({
            .label = "Browser Element",
        });

        current_dir = editor_asset_dir;
    }

    void content_browser_panel::render()
    {
        window->render(
            [this]()
            {
                if (current_dir != editor_asset_dir)
                {
                    back_button->render();
                }

                for (const auto& it :
                    std::filesystem::directory_iterator(current_dir))
                {
                    bool is_directory = it.is_directory();
                    browser_element->set_label(it.path().filename().string());

                    browser_element->render();

                    if (is_directory && browser_element->is_pressed())
                    {
                        current_dir /= it.path().filename();
                    }
                }
            });
    }

    void content_browser_panel::set_editor_asset_dir(
        const std::filesystem::path& path, bool set_current_dir)
    {
        editor_asset_dir = path;
        if (set_current_dir)
        {
            current_dir = path;
        }
    }
}
