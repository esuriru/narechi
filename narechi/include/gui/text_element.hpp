#pragma once

#include "core/core.hpp"
#include "element.hpp"

#include <string>
#include <optional>

namespace narechi::gui
{
    struct text_element_properties
    {
        std::string text;
        float scale = 1.0f;

        // TODO - Flags
        std::optional<float> truncate_width = std::nullopt;
    };

    class NRC_API text_element : public element
    {
    public:
        static sptr<text_element> create(const text_element_properties& props);

        virtual void set_text(const std::string& text);
        virtual void set_scale(float scale);
        virtual void set_truncate_width(float truncate_width);

    protected:
        text_element(const text_element_properties& props);

        text_element_properties props;
    };
}