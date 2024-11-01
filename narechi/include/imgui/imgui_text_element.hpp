#include "gui/text_element.hpp"

namespace narechi
{
    class imgui_text_element : public gui::text_element
    {
    public:
        imgui_text_element(const gui::text_element_properties& props);

        void set_text(const std::string& text) override;
        void set_truncate_width(float truncate_width) override;
        void render() override;

    private:
        std::string truncate_text_for_element(
            const std::string& text, float width);

        std::string truncated_string {};
        bool is_dirty = false;
    };
}