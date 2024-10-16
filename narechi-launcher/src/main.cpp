#include "core/core.hpp"

#include "editor_app.hpp"

int main()
{
    {
        narechi::make_uptr<narechi::editor::editor_app>()->run();
    }

    return 0;
}