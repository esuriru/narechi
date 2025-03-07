#include "editor_layer.hpp"

#include "asset/component_def_asset.hpp"
#include "asset/sprite_asset.hpp"
#include "entity_selection_context.hpp"
#include "file_extensions.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "graphics/framebuffer.hpp"
#include "panels/content_browser_panel.hpp"
#include "panels/scene_hierarchy_panel.hpp"
#include "panels/sprite_import_panel.hpp"
#include "scene/scene.hpp"
#include "asset/asset_extensions.hpp"
#include "utils/file_utils.hpp"
#include "scene/component.hpp"
#include "script/lua_script.hpp"

#include <filesystem>
#include <unordered_set>

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
                            .title = "Show Asset Dir in Explorer",
                            .callback =
                                [this]()
                            {
                                utils::file::open_explorer_in_dir(asset_dir);
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
                                build_panel->get_window()->set_active(true);
                            },
                        }
                    },
                },
                {
                    .title = "Asset",
                    .sub_menu_items = 
                    { 
                        {
                            .title = "Recompile Scripts",
                            .callback =
                                [this]()
                            {
                                if (!current_scene)
                                {
                                    return;
                                }

                                namespace s = narechi::scene;
                                import_scripts();
                                current_scene->get_world().query<
                                    s::component::lua_script>()
                                    .each([](
                                        s::component::lua_script& script)
                                    {
                                        auto& app = app::get();
                                        auto& database = 
                                            app.get_asset_database();
                                        auto lua_script_meta_asset = 
                                            database.get_asset<
                                            asset::lua_script_meta_asset>(
                                            script.script_asset_guid);
                                        if (lua_script_meta_asset)
                                        {
                                            lua_script_meta_asset->compile();
                                            lua_script_meta_asset->get_script()
                                                ->call(script::func_type::init);
                                        }
                                    });
                            },
                        },
                        {
                            .title = "Import Sprite",
                            .callback =
                                [this]()
                            {
                                sprite_import_panel->get_window()
                                    ->set_active(true);
                            },
                        },
                        {
                            .title = "Scan for Component definitions",
                            .callback =
                                [this]()
                            {
                                using namespace std::filesystem;

                                if (component_def_asset)
                                {
                                    NRC_CORE_LOG(
                                        "Component definition already exists");
                                    return;
                                }

                                for (const auto& it :
                                    recursive_directory_iterator(
                                        asset_dir))
                                {
                                    if (it.is_regular_file())
                                    {
                                        namespace a = narechi::asset;
                                        if (it.path().extension()
                                            == a::extension<a::component_def_asset>
                                                ::value)
                                        {
                                            component_def_asset
                                                = a::component_def_asset::load(
                                                    it.path());
                                            if (component_def_asset)
                                            {
                                                // Import user-defined 
                                                // components
                                                ecs_script_run(
                                                    current_scene->get_world(),
                                                    "User-defined Components",
                                                    component_def_asset
                                                        ->get_code()
                                                        .c_str());
                                            }
                                            if (build_panel)
                                            {
                                                build_panel->set_cdef_asset(
                                                    component_def_asset);
                                            }
                                            app::get()
                                                .get_asset_database()
                                                .add_asset(
                                                    component_def_asset);
                                        }
                                    }
                                }
                            }
                        }
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
                                on_scene_select();

                                current_project->set_startup_scene_name(
                                    scene_name);
                                current_project->save();
                            },
                        },
                        {
                            .title = "Clone Selected Entity",
                            .callback = 
                                [this]()
                            {
                                if (!current_scene ||
                                    !entity_selection_ctx.active)
                                {
                                    return;
                                }

                                auto new_entity = 
                                    entity_selection_ctx.selected_entity.clone();

                                constexpr const char* cloned_entity_suffix = 
                                    " (Clone)";
                                std::string cloned_entity_name = 
                                    std::string(
                                        entity_selection_ctx.selected_entity
                                            .name().c_str())
                                    + cloned_entity_suffix;

                                if (current_scene->get_world()
                                    .lookup(cloned_entity_name.c_str()) == 0)
                                {
                                    new_entity.set_name(
                                        cloned_entity_name.c_str());
                                    return;
                                }

                                int i = 1;
                                while (current_scene->get_world()
                                    .lookup(
                                        (cloned_entity_name + 
                                            " " + std::to_string(i))
                                        .c_str())
                                    > 0)
                                {
                                    i++;
                                }

                                new_entity.set_name(
                                    (cloned_entity_name + 
                                    " " + std::to_string(i)).c_str());
                            },
                        },
                        {
                            .title = "New Entity",
                            .callback = 
                                [this]()
                            {
                                if (current_scene)
                                {
                                    constexpr const char* default_entity_name = 
                                        "New Entity";
                                    if (current_scene->get_world()
                                        .lookup(default_entity_name) == 0)
                                    {
                                        current_scene->add_entity(
                                            default_entity_name);
                                        return;
                                    }

                                    int i = 1;
                                    while (current_scene->get_world()
                                        .lookup(
                                            (std::string(default_entity_name) + 
                                                " " + std::to_string(i))
                                            .c_str())
                                        > 0)
                                    {
                                        i++;
                                    }

                                    current_scene->add_entity(
                                        (std::string(default_entity_name) + 
                                        " " + std::to_string(i)));
                                }
                            },
                        },
                        {
                            .title = "New Empty Sprite",
                            .callback = 
                                [this]()
                            {
                                if (current_scene)
                                {
                                    constexpr const char* default_entity_name = 
                                        "New Sprite";
                                    if (current_scene->get_world()
                                        .lookup(default_entity_name) == 0)
                                    {
                                        current_scene->add_empty_sprite(
                                            default_entity_name);
                                        return;
                                    }

                                    int i = 1;
                                    while (current_scene->get_world()
                                        .lookup(
                                            (std::string(default_entity_name) + 
                                                " " + std::to_string(i))
                                            .c_str())
                                        > 0)
                                    {
                                        i++;
                                    }

                                    current_scene->add_empty_sprite(
                                        (std::string(default_entity_name) + 
                                        " " + std::to_string(i)));
                                }
                            },
                        },
                    } 
                }, 
                { 
                    .title = "Component",
                    .sub_menu_items = 
                    { 
                        {
                            .title = "Add Scale",
                            .callback =
                                [this]()
                            {
                                if (entity_selection_ctx.active)
                                {
                                    using namespace narechi::scene;
                                    entity_selection_ctx.selected_entity
                                        .add<component::scale>();
                                }
                            },
                        },
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
        scene_hierarchy_panel = make_uptr<editor::scene_hierarchy_panel>();
        scene_hierarchy_panel->set_selection_context(&entity_selection_ctx);

        inspector_panel
            = make_uptr<editor::inspector_panel>(&entity_selection_ctx);

        build_panel = make_uptr<editor::build_panel>();
        build_panel->get_window()->set_enable_toggle(true);
        build_panel->get_window()->set_active(false);
        build_panel->set_cdef_asset(component_def_asset);

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
        sprite_import_panel->get_window()->set_enable_toggle(true);
        sprite_import_panel->get_window()->set_active(false);

        if (current_scene)
        {
            current_scene->awake();
            on_scene_select();
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
        scene_hierarchy_panel->render();
        inspector_panel->render();

        // Conditional render
        sprite_import_panel->render();
        build_panel->render();
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
                    current_scene
                        = scene::load(std::move(asset), component_def_asset);
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

        constexpr uint32_t allowed_definition_count = 1;
        uint32_t component_definitions = 0;
        auto& asset_database = app::get().get_asset_database();

        // TODO - Dirty code to change
        for (const auto& it :
            std::filesystem::recursive_directory_iterator(asset_dir))
        {
            if (it.is_regular_file())
            {
                auto extension = it.path().extension();
                if (extension == asset::extension<asset::sprite_asset>::value)
                {
                    std::filesystem::path sprite_asset_path = it.path();
                    sprite_asset_path.replace_extension(".png");
                    asset_database.add_asset(
                        asset::sprite_asset::load_data(sprite_asset_path));
                }
                else if (component_definitions < allowed_definition_count
                    && extension
                        == asset::extension<asset::component_def_asset>::value)
                {
                    component_def_asset
                        = asset::component_def_asset::load(it.path());
                    if (build_panel)
                    {
                        build_panel->set_cdef_asset(component_def_asset);
                    }
                    asset_database.add_asset(component_def_asset);
                    component_definitions++;
                }
            }
        }
    }

    void editor_layer::import_scripts()
    {
        if (!current_scene)
        {
            return;
        }

        auto& asset_database = app::get().get_asset_database();
        auto world = current_scene->get_world();

        std::vector<sptr<script::lua_script>> loaded_script_assets {};

        auto create_new_script_entity = [](flecs::world world,
                                            const std::string& name,
                                            const std::string& guid)
        {
            if (world.lookup(name.c_str()) == 0)
            {
                // Create script entity in world as it does not exist
                world.entity(name.c_str())
                    .set<narechi::scene::component::lua_script>({
                        .script_asset_guid = guid,
                    });
            }
        };

        for (const auto& it :
            std::filesystem::recursive_directory_iterator(asset_dir))
        {
            // Scan for lua scripts and create meta files if they don't exist
            if (it.is_regular_file())
            {
                if (loaded_scripts.contains(it.path().stem().string()))
                {
                    // Script is loaded, skip either meta or script
                    return;
                }

                auto extension = it.path().extension();
                if (extension
                    == asset::extension<asset::lua_script_meta_asset>::value)
                {
                    NRC_ASSERT(
                        std::filesystem::exists(
                            std::filesystem::path(it.path()).replace_extension(
                                script::lua_script::extension())),
                        "Script meta file exists but script does not");

                    auto meta_asset
                        = asset::lua_script_meta_asset::load_existing_script(
                            {
                                .world = world,
                                .ctx = app::get().get_sol2_context(),
                            },
                            it.path());
                    auto guid = asset_database.add_asset(meta_asset);
                    loaded_script_assets.push_back(meta_asset->get_script());

                    std::string filename = it.path().stem().string();
                    create_new_script_entity(world, filename, guid);
                    loaded_scripts.insert(filename);
                }
                else if (extension == script::lua_script::extension())
                {
                    if (std::filesystem::exists(
                            std::filesystem::path(it.path()).replace_extension(
                                asset::extension<
                                    asset::lua_script_meta_asset>::value)))
                    {
                        // Meta file exists already, so we wait to load using
                        // that
                        continue;
                    }

                    auto meta_asset = asset::lua_script_meta_asset::create(
                        {
                            .world = world,
                            .ctx = app::get().get_sol2_context(),
                        },
                        std::filesystem::path(it.path()).replace_extension(
                            asset::extension<
                                asset::lua_script_meta_asset>::value));
                    auto guid = asset_database.add_asset(meta_asset);
                    loaded_script_assets.push_back(meta_asset->get_script());

                    std::string filename = it.path().stem().string();
                    create_new_script_entity(world, filename, guid);
                    loaded_scripts.insert(filename);
                }
            }
        }

        // Re-run init functions
        for (auto& script : loaded_script_assets)
        {
            script->call(script::func_type::init);
        }
    }

    // To be called when `current_scene` is populated
    void editor_layer::on_scene_select()
    {
        // Import component definition file
        flecs::world world = current_scene->get_world();

        import_scripts();

        // // Run scripts
        // if (true)
        // {
        //     flecs::entity rotation_component = world.lookup("rotation");
        //     if (rotation_component > 0)
        //     {
        //         flecs::entity test_entity
        //             = world.entity().add(rotation_component);
        //         void* raw_rotation_component
        //             = test_entity.ensure(rotation_component);

        //         flecs::cursor cursor = world.cursor(
        //             rotation_component, raw_rotation_component);
        //         cursor.push();
        //         cursor.set_float(20.0f);
        //         cursor.pop();

        //         test_script = make_uptr<script::lua_script>(
        //             script::lua_script_deps {
        //                 .world = world,
        //                 .ctx = app::get().get_sol2_context(),
        //             },
        //             R"(
        //             function
        //             position_test(narechi__scene__component__position,
        //             narechi__scene__component__scale)
        //                 local position = narechi__scene__component__position
        //                 position:set_float_depth(2,
        //                 position:get_float_depth(2) - .01)
        //             end

        //             function rotate_object(rotation)
        //                 rotation:set_float(rotation:get_float() + .01)
        //             end
        //         )");

        //         world.system("ScriptSystem")
        //             .kind(flecs::OnUpdate)
        //             .run(
        //                 [this](flecs::iter& it)
        //                 {
        //                     test_script->call();
        //                 });
        //     }
        // }

        scene_hierarchy_panel->set_world(current_scene->get_world());
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