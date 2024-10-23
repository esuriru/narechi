#include "panels/content_browser_panel.hpp"

namespace narechi::editor
{
    content_browser_panel::content_browser_panel()
        : editor_panel("Content Browser")
        , window(gui::window::create({ .name = "Content Browser" }))
    {
        window->add_element(
            gui::text_element::create({ .text = "Content Browser Text" }));
        window->add_element(gui::text_element::create({ .text = "More Text" }));
    }

    void content_browser_panel::render()
    {
        window->render();
    }
}
