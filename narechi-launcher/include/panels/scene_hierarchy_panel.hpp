#pragma once

#include "entity_selection_context.hpp"
#include "narechi.hpp"

#include "panels/editor_panel.hpp"
#include "scene/component.hpp"

#include <filesystem>
#include <optional>

namespace narechi::editor
{
    class scene_hierarchy_panel : public editor_panel
    {
    public:
        scene_hierarchy_panel(std::optional<flecs::world> world = std::nullopt);

        void render() override;
        void set_world(flecs::world world);
        void set_selection_context(entity_selection_context* ctx);

    private:
        sptr<narechi::gui::window> window;

        sptr<narechi::scene::scene> current_scene;
        std::optional<flecs::world> scene_world = std::nullopt;
        flecs::query<scene::component::meta> scene_query {};

        entity_selection_context* selection_ctx = nullptr;
    };
}