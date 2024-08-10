#pragma once

namespace narechi
{
    class imgui_context final
    {
    public:
        imgui_context();

        void init();

        void new_frame();
        void render();

    private:
        bool has_init;
    };
}