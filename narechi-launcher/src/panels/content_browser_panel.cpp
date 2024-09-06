#include "panels/content_browser_panel.hpp"

namespace narechi::editor
{
    content_browser_panel::content_browser_panel()
        : editor_panel("Content Browser"),
          window(make_sptr<narechi::gui::window>("Content Browser"))
    {
    }

    void content_browser_panel::render()
    {
        window->render();
    }
}
