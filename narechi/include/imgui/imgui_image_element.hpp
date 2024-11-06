#pragma once

#include "gui/image_element.hpp"

struct ImVec2;

namespace narechi
{
    class imgui_image_element : public gui::image_element
    {
    public:
        imgui_image_element(const gui::image_element_properties& props);

        void render() override;

    private:
        const ImVec2 get_image_size();
    };
}