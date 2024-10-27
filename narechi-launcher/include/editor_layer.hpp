#pragma once

#include "narechi.hpp"
#include "panels/content_browser_panel.hpp"
#include "project.hpp"

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

    private:
        std::filesystem::path asset_dir;
        uptr<project> current_project;

        sptr<scene::scene> current_scene;

        sptr<gui::menu_bar> menu_bar;
        uptr<content_browser_panel> content_browser_panel;
    };
}