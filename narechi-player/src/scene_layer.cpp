#include "scene_layer.hpp"
#include "asset/component_def_asset.hpp"
#include "glm/ext/matrix_clip_space.hpp"

#include <filesystem>
#include <unordered_set>

namespace narechi::player
{
    scene_layer::scene_layer()
        : layer("SceneLayer")
    {
    }

    void scene_layer::on_attach()
    {
        using namespace asset;

        NRC_CORE_LOG("Attempting to load scene");
        std::filesystem::path asset_dir
            = std::filesystem::current_path() / "assets";

        // TODO - Is this required?
        // constexpr uint32_t allowed_definition_count = 1;
        // uint32_t component_definitions = 0;
        // sptr<component_def_asset> scene_component_def_asset {};

        for (const auto& it : std::filesystem::directory_iterator(asset_dir))
        {
            if (!it.is_regular_file())
            {
                continue;
            }

            // Load scene
            if (it.path().extension() == extension<scene_asset>::value)
            {
                current_scene = scene::scene::load(it.path(), nullptr);
                NRC_VERIFY(current_scene,
                    "Could not load scene at path: ",
                    it.path().string());
                NRC_CORE_LOG("Scene loaded: ", current_scene->get_name());
            }

            // Load sprites
            if (it.path().extension() == extension<sprite_asset>::value)
            {
                std::filesystem::path image_path = it.path();
                image_path.replace_extension(".png");

                app::get().get_asset_database().add_asset(
                    sprite_asset::load_data(image_path));
                NRC_CORE_LOG("Image loaded: ", image_path.string());
            }

            // TODO - Is this needed?
            // Load component definition file
            // if (it.path().extension() ==
            // extension<component_def_asset>::value
            //     && component_definitions < allowed_definition_count)
            // {
            //     scene_component_def_asset
            //         = component_def_asset::load(it.path());
            //     app::get().get_asset_database().add_asset(
            //         scene_component_def_asset);
            //     component_definitions++;
            // }
        }

        if (!current_scene)
        {
            NRC_CORE_WARN("There is no scene in the directory");
        }
        else
        {
            // Now, attempt to import scene-dependent assets like scripts

            // TODO - Is this needed?
            // Load component definition

            // Load scripts
            import_scripts(asset_dir);
        }

        auto& window = app::get().get_window();
        invalidate_proj_matrix(window.get_width(), window.get_height());
    }

    void scene_layer::on_update(float delta_time)
    {
        if (current_scene)
        {
            current_scene->update(delta_time);
        }
    }

    void scene_layer::on_event(event& event)
    {
        event_handler handler(event);

        handler.handle<window_resize_event>(
            [this](window_resize_event& event)
            {
                graphics::render_command::set_viewport(
                    0, 0, event.get_width(), event.get_height());
                invalidate_proj_matrix(event.get_width(), event.get_height());
                return false;
            });
    }

    void scene_layer::import_scripts(const std::filesystem::path& asset_dir)
    {
        NRC_CORE_LOG("Attempting to load scripts");

        auto& asset_database = app::get().get_asset_database();
        auto world = current_scene->get_world();

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

        std::unordered_set<std::string> loaded_scripts {};

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

                    auto guid = asset_database.add_asset(
                        asset::lua_script_meta_asset::load_existing_script(
                            {
                                .world = world,
                                .ctx = app::get().get_sol2_context(),
                            },
                            it.path()));

                    std::string filename = it.path().stem().string();
                    create_new_script_entity(world, filename, guid);

                    NRC_CORE_LOG("Script loaded: ", filename);
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

                    auto guid = asset_database.add_asset(
                        asset::lua_script_meta_asset::create(
                            {
                                .world = world,
                                .ctx = app::get().get_sol2_context(),
                            },
                            std::filesystem::path(it.path()).replace_extension(
                                asset::extension<
                                    asset::lua_script_meta_asset>::value)));

                    std::string filename = it.path().stem().string();
                    create_new_script_entity(world, filename, guid);

                    NRC_CORE_LOG("Script loaded: ", filename);
                    loaded_scripts.insert(filename);
                }
            }
        }
    }

    void scene_layer::invalidate_proj_matrix(float width, float height)
    {
        float scale = 0.05f;
        float p_width = (static_cast<float>(width) * scale) / 2;
        float p_height = (static_cast<float>(height) * scale) / 2;
        graphics::render2d::set_proj_matrix(
            glm::ortho(-p_width, p_width, -p_height, p_height, -10.0f, 10.0f));
    }
}
