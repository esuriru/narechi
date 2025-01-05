#include "panels/scene_hierarchy_panel.hpp"

#include "scene/component.hpp"

namespace narechi::editor
{
    scene_hierarchy_panel::scene_hierarchy_panel(
        std::optional<flecs::world> world)
        : editor_panel("Scene Hierarchy")
        , window(gui::window::create({ .name = this->name }))
        , scene_world(world)
    {
        if (world.has_value())
        {
            scene_query = world.value().query<scene::component::meta>();
        }
    }

    void scene_hierarchy_panel::render()
    {
        window->render(
            [&]()
            {
                if (!scene_world.has_value())
                {
                    return;
                }

                // scene_query.each(
                //     [this](flecs::entity e, scene::component::meta)
                //     {
                //         auto tree_scope =
                //         gui::scope::tree_node_scope::create(
                //             { .label = std::string(e.name().c_str()) });
                //     });
            });
    }

    void scene_hierarchy_panel::set_world(flecs::world world)
    {
        scene_world = world;
    }
}
