#include "panels/sprite_import_panel.hpp"
#include "gui/button_element.hpp"
#include "utils/file_utils.hpp"

namespace narechi::editor
{
    sprite_import_panel::sprite_import_panel()
        : editor_panel("Sprite Import")
        , window(gui::window::create(
              { .name = "Sprite Import", .width = 600, .height = 800 }))
    {
        constexpr float width = 350.0f;

        image_directory_input = gui::text_input_element::create({
            .width = width,
            .label_on_left = true,
            .label = "Image directory",
        });

        image_select_directory_button = gui::button_element::create({
            .same_line = true,
            .label = "Dir",
            .on_click =
                [this]()
            {
                auto file_path = utils::file::open_file_dialog(
                    { .filters = { { { ".png", "png" } } } });
                if (file_path.has_value())
                {
                    image_directory_input->set_text(file_path.value());
                }
            },
        });

        import_button = gui::button_element::create({ .label = "Import",
            .on_click = [this]()
            {
                app::get().get_asset_database().add_asset(
                    asset::sprite_asset::create(
                        image_directory_input->get_text()));
                window->set_active(false);
            } });

        window->add_element(gui::text_element::create(
            { .text = "Image must be in assets directory" }));
        window->add_element(image_directory_input);
        window->add_element(image_select_directory_button);
        window->add_element(import_button);
    }

    void sprite_import_panel::render()
    {
        window->render();
    }

    void sprite_import_panel::set_editor_asset_dir(
        const std::filesystem::path& dir)
    {
        asset_dir = dir;
    }

    sptr<narechi::gui::window> sprite_import_panel::get_window() const
    {
        return window;
    }
}