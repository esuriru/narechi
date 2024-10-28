#include "panels/content_browser_panel.hpp"
#include "gui/button_element.hpp"
#include "rendering/image.hpp"
#include "rendering/texture2d.hpp"

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

                int i = 0;
                for (const auto& it :
                    std::filesystem::directory_iterator(current_dir))
                {
                    browser_element->set_custom_uid(std::to_string(i++));

                    bool is_directory = it.is_directory();
                    browser_element->set_width(browser_element_size);
                    browser_element->set_height(browser_element_size);

                    browser_element->set_label(it.path().filename().string());

                    browser_element->set_texture(
                        is_directory ? folder_icon_texture : file_icon_texture);

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

        // NOTE - Temporary code to move after packing assets
        rendering::image_load_options options { .flip_vertically = false };
        file_icon_texture = rendering::texture2d::load(
            editor_asset_dir / "file-icon.png", options);
        folder_icon_texture = rendering::texture2d::load(
            editor_asset_dir / "folder-icon.png", options);
        browser_element = gui::image_button_element::create(
            {
                .same_line = true,
                .label = "Browser Element",
                .width = browser_element_size,
                .height = browser_element_size,
            },
            file_icon_texture);
    }
}
