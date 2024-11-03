#include "editor_layer.hpp"

#include "file_extensions.hpp"
#include "panels/content_browser_panel.hpp"
#include "panels/sprite_import_panel.hpp"
#include "scene/scene.hpp"

#include <filesystem>

namespace narechi::editor
{
    using scene::scene;

    editor_layer::editor_layer()
        : layer("EditorLayer")
        , current_scene(nullptr)
        , render_sprite_import_panel(false)
    {
        menu_bar = gui::menu_bar::create({
            .menu_items = { 
                {
                    .title = "File",
                    .sub_menu_items = 
                    { 
                        {
                            .title = "Open File",
                            .callback =
                                []()
                            {
                            },
                        },
                        {
                            .title = "Save Scene",
                            .callback =
                                [this]()
                            {
                                if (current_scene)
                                {
                                    current_scene->save();
                                }
                            },
                        },
                    },
                },
                {
                    .title = "Asset",
                    .sub_menu_items = 
                    { 
                        {
                            .title = "Import Sprite",
                            .callback =
                                [this]()
                            {
                                render_sprite_import_panel = true;
                            },
                        },
                    },
                },
                { 
                    .title = "Scene",
                    .sub_menu_items = 
                    { 
                        {
                            .title = "Create Scene",
                            .callback =
                                [this]()
                            {
                                std::string scene_name = "New Scene";
                                std::filesystem::path scene_path = 
                                    asset_dir / 
                                    (scene_name + scene_file_extension);
                                
                                if (scene_path.has_parent_path())
                                {
                                    std::filesystem::create_directories(
                                        scene_path.parent_path());
                                }

                                current_scene = scene::create(
                                    scene_path, scene_name);
                                current_scene->awake();

                                current_project->set_startup_scene_name(
                                    scene_name);
                                current_project->save();
                            },
                        },
                        {
                            .title = "Add Entity",
                            .callback = 
                                [this]()
                            {
                                if (current_scene)
                                {
                                    current_scene->add_entity();
                                }
                            },
                        }
                    } 
                }, 
            },
        });
    }

    editor_layer::~editor_layer()
    {
    }

    void editor_layer::on_attach()
    {
        NRC_ASSERT(!asset_dir.empty(), "Editor loaded without a project");

        content_browser_panel = make_uptr<editor::content_browser_panel>();
        content_browser_panel->set_editor_asset_dir(asset_dir, true);

        sprite_import_panel = make_uptr<editor::sprite_import_panel>();

        if (current_scene)
        {
            current_scene->awake();
        }
    }

    void editor_layer::on_detach()
    {
    }

    void editor_layer::on_gui_update()
    {
        menu_bar->render();
        content_browser_panel->render();
        if (render_sprite_import_panel)
        {
            sprite_import_panel->render();
        }
    }

    void editor_layer::on_update(float dt)
    {
        if (current_scene)
        {
            current_scene->update(dt);
        }
    }

    void editor_layer::on_event(event& event)
    {
        static std::vector<editor_panel*> panels {
            content_browser_panel.get()
        };

        for (auto& panel : panels)
        {
            if (event.handled)
            {
                break;
            }

            panel->on_event(event);
        }
    }

    void editor_layer::set_project(uptr<project> project)
    {
        current_project = std::move(project);
        app::get().get_window().set_title(current_project->get_data().name);
        asset_dir = current_project->get_path().parent_path() / "assets";

        load_scene_from_project();
    }

    void editor_layer::load_scene_from_project()
    {
        if (current_project->get_data().startup_scene_name.empty())
        {
            return;
        }

        if (!std::filesystem::exists(asset_dir))
        {
            return;
        }

        for (const auto& it : std::filesystem::directory_iterator(asset_dir))
        {
            if (it.is_regular_file()
                && it.path().extension() == scene_file_extension)
            {
                uptr<asset::scene_asset> asset
                    = asset::scene_asset::load_data(it.path());
                if (asset->get_scene_data().name
                    == current_project->get_data().startup_scene_name)
                {
                    current_scene = scene::load(std::move(asset));
                    NRC_CORE_LOG(
                        "Startup scene loaded: ", current_scene->get_name());
                }
            }
        }
    }
}