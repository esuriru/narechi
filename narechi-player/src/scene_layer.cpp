#include "scene_layer.hpp"
#include "glm/ext/matrix_clip_space.hpp"

#include <filesystem>

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
        for (const auto& it : std::filesystem::directory_iterator(asset_dir))
        {
            // Load scene
            if (it.is_regular_file()
                && it.path().extension() == extension<scene_asset>::value)
            {
                current_scene = scene::scene::load(it.path());
                NRC_VERIFY(current_scene,
                    "Could not load scene at path: ",
                    it.path().string());
                NRC_CORE_LOG("Scene loaded: ", current_scene->get_name());
            }

            // Load sprites
            if (it.is_regular_file()
                && it.path().extension() == extension<sprite_asset>::value)
            {
                std::filesystem::path image_path = it.path();
                image_path.replace_extension(".png");

                app::get().get_asset_database().add_asset(
                    sprite_asset::load_data(image_path));
                NRC_CORE_LOG("Image loaded: ", image_path.string());
            }
        }

        if (!current_scene)
        {
            NRC_CORE_WARN("There is no scene in the directory");
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

    void scene_layer::invalidate_proj_matrix(float width, float height)
    {
        float scale = 0.05f;
        float p_width = (static_cast<float>(width) * scale) / 2;
        float p_height = (static_cast<float>(height) * scale) / 2;
        graphics::render2d::set_proj_matrix(
            glm::ortho(-p_width, p_width, -p_height, p_height, -10.0f, 10.0f));
    }
}
