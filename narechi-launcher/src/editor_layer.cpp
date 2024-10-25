#include "editor_layer.hpp"

#include "file_extensions.hpp"
#include "panels/content_browser_panel.hpp"
#include "scene/scene.hpp"
#include <exception>
#include <filesystem>

namespace narechi::editor
{
    using scene::scene;

    editor_layer::editor_layer()
        : layer("EditorLayer")
        , current_scene(nullptr)
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
                                    asset_directory / 
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
        panels.push_back(make_uptr<content_browser_panel>());

        if (current_scene)
        {
            current_scene->awake();
        }
    }

    void editor_layer::on_detach()
    {
        panels.clear();
    }

    void editor_layer::on_gui_update()
    {
        menu_bar->render();
        for (auto& panel : panels)
        {
            panel->render();
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
        asset_directory = current_project->get_path().parent_path() / "assets";

        load_scene_from_project();
    }

    void editor_layer::load_scene_from_project()
    
    {
        if (current_project->get_data().startup_scene_name.empty())
        {
            return;
        }

        if (!std::filesystem::exists(asset_directory))
        {
            return;
        }

        for (const auto& it :
            std::filesystem::directory_iterator(asset_directory))
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