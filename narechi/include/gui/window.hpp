#pragma once

#include "core/core.hpp"

#include <string>

namespace narechi::gui
{
    class NRC_API window
    {
    public:
        window(std::string&& name);

        void render();

    private:
        std::string name;
    };
}