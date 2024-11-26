#include "panels/build_panel.hpp"
#include "file_extensions.hpp"
#include "utils/file_utils.hpp"
#include "asset/embed.hpp"
#include "asset/asset_extensions.hpp"

#include <filesystem>
#include <fstream>

// Embedded player executable
NRC_DECL_EMBED_BYTE_ARRAY(narechi_player)

// Embedded engine shared library
NRC_DECL_EMBED_BYTE_ARRAY(libnarechi_engine)

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
                // TODO - Unable to build if no scene exists
                NRC_ASSERT(export_scene, "No scene to export");
                NRC_CORE_LOG("Build initiated");

                std::filesystem::path build_dir(
                    build_directory_input->get_text());

                NRC_CORE_LOG("Unpacking and creating player executable");
                {
                    std::ofstream out_player_stream;
                    out_player_stream.open(
                        build_dir / "player.exe", std::ios::binary);
                    out_player_stream.write(
                        reinterpret_cast<const char*>(embed::narechi_player),
                        embed::narechi_player_length);
                }

                NRC_CORE_LOG("Unpacking and creating engine DLL");
                {
                    std::ofstream out_player_stream;
                    out_player_stream.open(
                        build_dir / "libnarechi-engine.dll", std::ios::binary);
                    out_player_stream.write(
                        reinterpret_cast<const char*>(embed::libnarechi_engine),
                        embed::libnarechi_engine_length);
                }

                NRC_CORE_LOG("Exporting scene as raw files");
                {
                    std::filesystem::path asset_dir = build_dir / "assets";
                    if (!std::filesystem::exists(asset_dir))
                    {
                        std::filesystem::create_directories(asset_dir);
                    }

                    // Export asset to new asset directory
                    export_scene->export_to_dir(asset_dir);
                }
            },
        }));
    }

    void build_panel::render()
    {
        window->render();
    }

    void build_panel::set_export_scene(sptr<scene::scene> scene)
    {
        export_scene = scene;
    }
}