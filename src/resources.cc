#include "resources.hh"
#include <stdexcept>

Resources::Resources()
{
    init_sdl();
    init_values();
    init_winren();
    load_fonts();
}

Resources::~Resources()
{
    free_winren();
    free_sdl();
}

void Resources::window_clear()
{
    SDL_SetRenderDrawColor(
        renderer,
        color_back.r,
        color_back.g,
        color_back.b,
        color_back.a);
    SDL_RenderClear(renderer);
}

void Resources::window_draw()
{
    SDL_RenderPresent(renderer);
}

void Resources::init_sdl()
{
    // SDL2 itself
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        SDL_Log("Error in initializing SDL");
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Log("SDL initialized");

    // SDL2 IMG
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_Log("Error in initializing SDL_IMG");
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Log("SDL_IMG initialized");

    // SDL2 TTF
    if(TTF_Init())
    {
        SDL_Log("Error in initializing SDL_TTF");
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Log("SDL_TTF initialized");
}

void Resources::init_values()
{
    screen_w = 800;
    screen_h = 600;
    game_running = true;

    color_back = {30, 0, 0, 0};
    color_white = {255, 255, 255, 0};
}

void Resources::init_winren()
{
    window = SDL_CreateWindow(
        "SpaceSurf",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600, 0);
    if(!window)
    {
        SDL_Log("Error in creating window");
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Log("Window created");

    renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        SDL_Log("Error in creating renderer");
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Log("Renderer created");
}

void Resources::load_fonts()
{
    font_m = TTF_OpenFont("../res/fonts/slkscr.ttf", 32);
}

void Resources::free_sdl()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    SDL_Log("SDL has been quit");
}

void Resources::free_winren()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Log("Window and renderer destroyed");
}
