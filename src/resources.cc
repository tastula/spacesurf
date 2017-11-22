#include "resources.hh"
#include <stdexcept>

Resources::Resources()
{
    init_sdl();
    init_values();
    init_winren();
}

void Resources::init_sdl()
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        SDL_Log("Error in initializing SDL.");
        throw runtime_error(SDL_GetError());
    }
    SDL_Log("SDL initialized.");
}
