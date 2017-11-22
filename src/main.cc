#include "resources.hh"
#include <SDL2/SDL.h>

int main()
{
    Resources res;

    res.window_clear();
    res.window_draw();
    SDL_Delay(2000);

    return 0;
}
