#include "imgui/imgui_button_element.hpp"

namespace narechi
{
    class imgui_image_button_element : public imgui_button_element
    {
    public:
        imgui_image_button_element(const gui::button_element_properties& props);

        bool imgui_button_call() override;
    };
}