#include "resources.hh"
#include <SDL2/SDL.h>

int main()
{
    Resources res;

    // Run the game
    while(res.game_running)
    {
        res.window_clear();

        // Check for user events
        while(SDL_PollEvent(&res.event))
        {
            if(res.event.type == SDL_QUIT) return 0;
        }

        res.window_draw();
    }

    return 0;
}
