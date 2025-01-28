#pragma once

#include "entity_selection_context.hpp"
#include "gui/button_element.hpp"
#include "gui/text_element.hpp"
#include "gui/text_input_element.hpp"
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
        enum class add_component_result
        {
            none,
            selection_ctx_null,
            component_does_not_exist,
            component_already_added,
            successful
        };

        add_component_result add_component(const std::string& component_name);
        const char* get_add_component_message() const;

        sptr<narechi::gui::window> window;

        sptr<narechi::gui::text_element> entity_name_element;

        sptr<narechi::gui::text_input_element> component_input_element;
        sptr<narechi::gui::button_element> add_component_button;

        entity_selection_context* selection_ctx = nullptr;
        add_component_result current_result = add_component_result::none;
    };
}