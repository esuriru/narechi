#include "panels/content_browser_panel.hpp"

namespace narechi::editor
{
    content_browser_panel::content_browser_panel()
        : editor_panel("Content Browser"), window(gui::window::create({
                                               .name = "Content Browser",
                                               .width = 200,
                                               .height = 720,
                                               .start_position_x = 0,
                                               .start_position_y = 0,
                                           }))
    {
        window->add_element(
            gui::text_element::create({ .text = "Content Browser Text" }));
        window->add_element(gui::text_element::create({ .text = "More Text" }));
    }

    void content_browser_panel::render()
    {
        window->render();
    }

    void content_browser_panel::on_event(event& event)
    {
        event_handler handler(event);

        handler.handle<window_resize_event>(
            [this](auto& event)
            {
                window->set_width_height(
                    window->get_width(), event.get_height());
                return false;
            });
    }
}
