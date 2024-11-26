#include "panels/build_panel.hpp"
#include "utils/file_utils.hpp"
#include "asset/embed.hpp"

#include <fstream>

// Embedded player executable
NRC_DECL_EMBED_BYTE_ARRAY(narechi_player)

namespace narechi::editor
{
    build_panel::build_panel()
        : editor_panel("Build")
        , window(gui::window::create(
              { .name = "Build Application", .width = 600, .height = 800 }))
    {
        constexpr float width = 350.0f;

        build_directory_input = gui::text_input_element::create({
            .width = width,
            .label_on_left = true,
            .label = "Build directory",
        });

        build_directory_button = gui::button_element::create({
            .same_line = true,
            .label = "Dir",
            .on_click =
                [this]()
            {
                auto folder_path = utils::file::pick_folder();
                if (folder_path.has_value())
                {
                    build_directory_input->set_text(folder_path.value());
                }
            },
        });

        window->add_element(build_directory_input);
        window->add_element(build_directory_button);
        window->add_element(gui::button_element::create({
            .label = "Build",
            .on_click =
                [this]()
            {
                NRC_CORE_LOG("Build initiated");
                std::ofstream out_player_stream;
                out_player_stream.open(
                    std::filesystem::path(build_directory_input->get_text())
                        / "player.exe",
                    std::ios::binary | std::ios::app);
                out_player_stream.write(
                    reinterpret_cast<const char*>(embed::narechi_player),
                    embed::narechi_player_length);
            },
        }));
    }

    void build_panel::render()
    {
        window->render();
    }
}