#include "gui/text_input_element.hpp"

namespace narechi
{
    class imgui_text_input_element : public gui::text_input_element
    {
    public:
        imgui_text_input_element(
            const gui::text_input_element_properties& props);

        float get_label_length() override;
        void render() override;

    private:
        float label_length;
    };
}