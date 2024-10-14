#include "gui/space_element.hpp"

namespace narechi
{
    class imgui_space_element : public gui::space_element
    {
    public:
        imgui_space_element(const gui::space_element_properties& props);

        void render() override;
    };
}