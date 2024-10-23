#include "gui/menu_bar.hpp"

namespace narechi
{
    class imgui_menu_bar : public gui::menu_bar
    {
    public:
        imgui_menu_bar(const gui::menu_bar_properties& props);

        void render() override;
    };
}