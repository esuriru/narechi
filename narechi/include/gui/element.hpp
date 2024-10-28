#pragma once

#include "core/core.hpp"

#include <string>

namespace narechi::gui
{
    // GUI Window element
    class NRC_API element
    {
    public:
        element();

        virtual void render() = 0;
        void generate_uid();
        void set_custom_uid(const std::string& uid);

    protected:
        std::string uid;
    };
}