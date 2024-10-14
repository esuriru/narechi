#pragma once

namespace narechi::gui
{
    // GUI Window element
    class element
    {
    public:
        virtual void render() = 0;
    };
}