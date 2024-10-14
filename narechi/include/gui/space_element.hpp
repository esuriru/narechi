#pragma once

#include "core/core.hpp"
#include "element.hpp"

namespace narechi::gui
{
    struct space_element_properties
    {
        uint32_t lines = 1;
    };

    class NRC_API space_element : public element
    {
    public:
        static sptr<space_element> create(
            const space_element_properties& props);

    protected:
        space_element(const space_element_properties& props);

        space_element_properties props;
    };
}