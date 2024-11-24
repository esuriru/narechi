#include "narechi.hpp"

#include "player_app.hpp"

int main()
{
    {
        narechi::make_uptr<narechi::player::player_app>()->run();
    }

    return 0;
}