#pragma once

#include "core/core.hpp"
#include "element.hpp"

namespace narechi::gui
{
    struct table_element_properties
    {
        uint32_t rows = 1;
        uint32_t columns = 1;
    };

    class NRC_API table_element : public element
    {
    public:
        static sptr<table_element> create(
            const table_element_properties& props);

        virtual void fill_up_row(uint32_t row, sptr<element> element) = 0;

    protected:
        table_element(const table_element_properties& props);

        table_element_properties props;
    };
}