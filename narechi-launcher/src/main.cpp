#include "editor_app.hpp"

int main()
{
    auto editor_app = new narechi::editor::editor_app();

    editor_app->run();

    delete editor_app;

    return 0;
}