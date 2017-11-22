#include <iostream>
#include <SDL2/SDL.h>

int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    std::cout << "SDL initialized." << std::endl;

    SDL_Window* window = SDL_CreateWindow(
        "SpaceSurf",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600, 0);

    if(window == nullptr)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
    }

    SDL_Delay(2000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
