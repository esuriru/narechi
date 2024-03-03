#include <core/app.hpp>

__declspec(dllexport) narechi::app* narechi::create_app();

// TODO - Arguments for app creation: App specification
int main()
{
    auto app = narechi::create_app();

    app->run();

    delete app;

    return 0;
}
