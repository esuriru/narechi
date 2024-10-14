#include "gui/text_element.hpp"

namespace narechi
{
    class imgui_text_element : public gui::text_element
    {
    public:
        imgui_text_element(const gui::text_element_properties& props);

        void render() override;
    };
}