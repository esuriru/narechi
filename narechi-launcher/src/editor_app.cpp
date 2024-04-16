#include "editor_app.hpp"

narechi::app* narechi::create_app()
{
    return new narechi::editor::editor_app();
}