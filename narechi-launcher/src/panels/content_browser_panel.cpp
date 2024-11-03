#include "panels/content_browser_panel.hpp"
#include "gui/button_element.hpp"
#include "gui/scope/table_scope.hpp"
#include "rendering/image.hpp"
#include "rendering/texture2d.hpp"

#include "asset/embed.hpp"

#include <deque>

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
                .same_line = false,
                .label = "Browser Element",
                .width = browser_element_size,
                .height = browser_element_size,
            },
            file_icon_texture);
        browser_text_element = gui::text_element::create({
            .text = "filename",
        });

        browser_table_props.label = "Content Browser Table";
        browser_table_props.flags
            = gui::scope::table_scope_flags::fit_columns_to_width;
    }

    void content_browser_panel::render()
    {
        using namespace gui::scope;

        window->render(
            [this]()
            {
                if (current_dir != editor_asset_dir)
                {
                    back_button->render();
                }

                float total_cell_size
                    = browser_element_padding + browser_element_size;
                browser_table_props.element_size = total_cell_size;
                browser_table_props.padding_x = browser_table_props.padding_y
                    = browser_element_padding;
                browser_text_element->set_truncate_width(
                    browser_element_size + browser_element_padding / 2);

                {
                    auto scope = table_scope::create(browser_table_props);

                    int i = 0;

                    std::deque<std::filesystem::directory_entry> entries {};

                    for (const auto& it :
                        std::filesystem::directory_iterator(current_dir))
                    {
                        if (it.is_directory())
                        {
                            entries.push_front(it);
                        }
                        else
                        {
                            entries.push_back(it);
                        }
                    }

                    for (const auto& it : entries)
                    {
                        scope->next_column();

                        bool is_directory = it.is_directory();
                        browser_element->set_width(browser_element_size);
                        browser_element->set_height(browser_element_size);

                        browser_element->set_custom_uid(
                            it.path().filename().string());

                        browser_element->set_texture(is_directory ?
                                folder_icon_texture :
                                file_icon_texture);
                        browser_text_element->set_text(
                            it.path().stem().string());

                        browser_element->render();
                        browser_text_element->render();

                        if (is_directory && browser_element->is_pressed())
                        {
                            current_dir /= it.path().filename();
                        }
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
