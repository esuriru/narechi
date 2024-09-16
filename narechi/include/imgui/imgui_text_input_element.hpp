#include "gui/text_input_element.hpp"

namespace narechi
{
    class imgui_text_input_element : public gui::text_input_element
    {
    public:
        imgui_text_input_element(
            const gui::text_input_element_properties& props);

        void render() override;
    };
}