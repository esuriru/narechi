#pragma once

#include "asset/component_def_asset.hpp"
#include "graphics/framebuffer.hpp"
#include "narechi.hpp"
#include "entity_selection_context.hpp"
#include "project.hpp"

#include "panels/content_browser_panel.hpp"
#include "panels/sprite_import_panel.hpp"
#include "panels/scene_view_panel.hpp"
#include "panels/build_panel.hpp"
#include "panels/scene_hierarchy_panel.hpp"
#include "panels/inspector_panel.hpp"
#include "script/lua_script.hpp"

// TODO - Will there be a need to separate the editor from the editor_layer?
namespace narechi::editor
{
    class editor_layer final : public layer
    {
    public:
        explicit editor_layer();
        ~editor_layer();

        void on_attach() override;
        void on_detach() override;

        void on_gui_update() override;
        void on_update(float dt) override;

        void on_event(event& event) override;

        void set_project(uptr<project> project);

        void load_scene_from_project();
        void import_assets();
        void import_scripts();

        void on_scene_select();

    private:
        std::filesystem::path asset_dir;
        uptr<project> current_project;

        sptr<scene::scene> current_scene;
        sptr<graphics::framebuffer> scene_framebuffer;
        sptr<asset::component_def_asset> component_def_asset;

        sptr<gui::menu_bar> menu_bar;

        uptr<content_browser_panel> content_browser_panel;
        uptr<sprite_import_panel> sprite_import_panel;
        uptr<scene_view_panel> scene_view_panel;
        uptr<build_panel> build_panel;
        uptr<scene_hierarchy_panel> scene_hierarchy_panel;
        uptr<inspector_panel> inspector_panel;

        uptr<script::lua_script> test_script;

        entity_selection_context entity_selection_ctx;

        void invalidate_proj_matrix();
    };
}