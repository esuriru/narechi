#include "gui/button_element.hpp"

namespace narechi
{
    class imgui_button_element : public gui::button_element
    {
    public:
        imgui_button_element(const gui::button_element_properties& props);

        void render() override;
    };
}