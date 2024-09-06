#include "panels/content_browser_panel.hpp"

namespace narechi::editor
{
    content_browser_panel::content_browser_panel()
        : editor_panel("Content Browser"),
          window(gui::window::create_window({ .name = "Content Browser" }))
    {
    }

    void content_browser_panel::render()
    {
        window->render();
    }
}
