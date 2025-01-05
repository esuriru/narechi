#include "panels/inspector_panel.hpp"

#include "gui/text_element.hpp"
#include "scene/component.hpp"
#include <stack>

namespace narechi::editor
{
    inspector_panel::inspector_panel(entity_selection_context* selection_ctx)
        : editor_panel("Inspector")
        , window(gui::window::create({ .name = this->name }))
        , selection_ctx(selection_ctx)
    {
        entity_name_element = gui::text_element::create({});

        window->add_element(entity_name_element);
        window->set_active(static_cast<bool>(selection_ctx));
    }

    void inspector_panel::render()
    {
        if (selection_ctx && selection_ctx->active)
        {
            entity_name_element->set_text(
                std::string(selection_ctx->selected_entity.name()));
        }

        window->render();
    }
}
