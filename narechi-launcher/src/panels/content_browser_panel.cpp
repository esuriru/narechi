#include "panels/content_browser_panel.hpp"
#include "gui/button_element.hpp"
#include "rendering/image.hpp"
#include "rendering/texture2d.hpp"

#include "asset/embed.hpp"

NRC_DECL_EMBED_BYTE_ARRAY(file_icon)
NRC_DECL_EMBED_BYTE_ARRAY(folder_icon)

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

        rendering::image_load_options options { .flip_vertically = false };

        file_icon_texture = rendering::texture2d::load_from_memory(
            embed::file_icon, embed::file_icon_length, options);
        folder_icon_texture = rendering::texture2d::load_from_memory(
            embed::folder_icon, embed::folder_icon_length, options);

        browser_element = gui::image_button_element::create(
            {
                .same_line = true,
                .label = "Browser Element",
                .width = browser_element_size,
                .height = browser_element_size,
            },
            file_icon_texture);
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
    }
}
