#include "panels/content_browser_panel.hpp"

namespace narechi::editor
{
    content_browser_panel::content_browser_panel()
        : editor_panel("Content Browser"),
          window(gui::window::create_window({ .name = "Content Browser",
              .start_position_x = 0,
              .start_position_y = 0 }))
    {
    }

    void content_browser_panel::render()
    {
        window->render();
    }
}
