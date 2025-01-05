#include "panels/scene_hierarchy_panel.hpp"

#include "scene/component.hpp"
#include <stack>

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
            scene_query = world.value()
                              .query_builder<scene::component::meta>()
                              .cached()
                              .build();
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

                scene_world.value().each(
                    [&](flecs::entity e, scene::component::meta)
                    {
                        gui::scope::tree_node_scope::create({
                            .id = e.id(),
                            .label = std::string(e.name()),
                        });
                    });
            });
    }

    void scene_hierarchy_panel::set_world(flecs::world world)
    {
        scene_world = world;
        scene_query
            = world.query_builder<scene::component::meta>().cached().build();
    }
}
