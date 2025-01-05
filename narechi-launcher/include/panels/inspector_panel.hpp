#pragma once

#include "entity_selection_context.hpp"
#include "gui/text_element.hpp"
#include "narechi.hpp"

#include "panels/editor_panel.hpp"

namespace narechi::editor
{
    class inspector_panel : public editor_panel
    {
    public:
        inspector_panel(entity_selection_context* selection_ctx = nullptr);

        void render() override;

    private:
        sptr<narechi::gui::window> window;

        sptr<narechi::gui::text_element> entity_name_element;

        entity_selection_context* selection_ctx = nullptr;
    };
}