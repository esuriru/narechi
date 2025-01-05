#pragma once

#include "narechi.hpp"

#include "panels/editor_panel.hpp"

namespace narechi::editor
{
    class inspector_panel : public editor_panel
    {
    public:
        inspector_panel();

        void render() override;

    private:
        sptr<narechi::gui::window> window;
    };
}