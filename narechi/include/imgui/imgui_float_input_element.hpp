#include "gui/float_input_element.hpp"

namespace narechi
{
    class imgui_float_input_element : public gui::float_input_element
    {
    public:
        imgui_float_input_element(
            const gui::float_input_element_properties& props);

        float get_label_length() override;
        void render() override;

    private:
        float label_length;
    };
}