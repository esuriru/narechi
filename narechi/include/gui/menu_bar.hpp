#pragma once

#include "core/core.hpp"

#include <vector>
#include <string>
#include <functional>

namespace narechi::gui
{
    struct menu_bar_properties
    {
        struct sub_menu_bar_item
        {
            std::string title;
            std::function<void()> callback;
        };

        struct menu_bar_item
        {
            std::string title;
            std::vector<sub_menu_bar_item> sub_menu_items;
        };

        std::vector<menu_bar_item> menu_items;
    };

    class NRC_API menu_bar
    {
    public:
        static sptr<menu_bar> create(const menu_bar_properties& props);

        virtual void render() = 0;

    protected:
        menu_bar(const menu_bar_properties& props);

        menu_bar_properties props;
    };
}