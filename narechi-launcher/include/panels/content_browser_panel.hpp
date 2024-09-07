#pragma once

#include "narechi.hpp"

#include "panels/editor_panel.hpp"

namespace narechi::editor
{
    class content_browser_panel : public editor_panel
    {
    public:
        content_browser_panel();

        void render() override;
        void on_event(event& event) override;

    private:
        sptr<narechi::gui::window> window;
    };
}