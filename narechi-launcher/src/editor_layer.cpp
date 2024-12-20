#include "editor_layer.hpp"

#include "asset/sprite_asset.hpp"
#include "file_extensions.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "graphics/framebuffer.hpp"
#include "panels/content_browser_panel.hpp"
#include "panels/sprite_import_panel.hpp"
#include "scene/scene.hpp"
#include "asset/asset_extensions.hpp"

#include <filesystem>

namespace narechi::editor
{
    using scene::scene;

    editor_layer::editor_layer()
        : layer("EditorLayer")
        , current_scene(nullptr)
        , render_sprite_import_panel(false)
        , render_build_panel(false)
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
                        {
                            .title = "Build and Export",
                            .callback =
                                [this]()
                            {
                                NRC_ASSERT(build_panel, 
                                    "Cannot build and export if build"
                                    " panel does not exist");
                                NRC_ASSERT(current_scene, 
                                    "Cannot build and export if no"
                                    " current scene exists");
                                build_panel->set_export_scene(current_scene);
                                render_build_panel = true;
                            },
                        }
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

        scene_framebuffer = graphics::framebuffer::create({
            .width = 1280 / 2,
            .height = 720 / 2,
        });

        scene_view_panel
            = make_uptr<editor::scene_view_panel>(scene_framebuffer);
        build_panel = make_uptr<editor::build_panel>();

        invalidate_proj_matrix();
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
        sprite_import_panel->set_editor_asset_dir(asset_dir);

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
        scene_view_panel->render();

        if (render_sprite_import_panel)
        {
            sprite_import_panel->render();
        }

        if (render_build_panel)
        {
            build_panel->render();
        }
    }

    void editor_layer::on_update(float dt)
    {
        scene_framebuffer->bind();
        // scene_framebuffer->clear_color(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
        // scene_framebuffer->clear_depth();

        if (current_scene)
        {
            current_scene->update(dt);
        }

        scene_framebuffer->unbind();
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

        import_assets();
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

    void editor_layer::import_assets()
    {
        if (!std::filesystem::exists(asset_dir))
        {
            return;
        }

        // TODO - Dirty code to change
        for (const auto& it :
            std::filesystem::recursive_directory_iterator(asset_dir))
        {
            if (it.is_regular_file()
                && it.path().extension()
                    == asset::extension<asset::sprite_asset>::value)
            {
                app::get().get_asset_database().add_asset(
                    asset::sprite_asset::load_data(it.path().parent_path()
                        / (it.path().stem().string() + ".png")));
            }
        }
    }

    void editor_layer::invalidate_proj_matrix()
    {
        float scale = 0.05f;
        float width
            = (static_cast<float>(scene_framebuffer->get_specification().width)
                  * scale)
            / 2;
        float height
            = (static_cast<float>(scene_framebuffer->get_specification().height)
                  * scale)
            / 2;
        graphics::render2d::set_proj_matrix(
            glm::ortho(-width, width, -height, height, -10.0f, 10.0f));
    }
}