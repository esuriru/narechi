#include "gui/table_element.hpp"

#include <vector>

namespace narechi
{
    class imgui_table_element : public gui::table_element
    {
    public:
        imgui_table_element(const gui::table_element_properties& props);

        void fill_up_row(uint32_t row, sptr<gui::element> element) override;

        void render() override;

    private:
        std::vector<std::vector<sptr<gui::element>>> elements;
    };
}