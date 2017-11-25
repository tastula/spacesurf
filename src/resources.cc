#include "resources.hh"
#include <stdexcept>

Resources::Resources()
{
    init_sdl();
    init_values();
    init_winren();
    load_fonts();
    load_textures();

    SDL_Log("Game initialized");
}

Resources::~Resources()
{
    free_fonts();
    free_textures();
    free_winren();
    free_sdl();

    SDL_Log("Game ended succesfully");
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

    // SDL2 IMG
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_Log("Error in initializing SDL_IMG");
        throw std::runtime_error(SDL_GetError());
    }

    // SDL2 TTF
    if(TTF_Init())
    {
        SDL_Log("Error in initializing SDL_TTF");
        throw std::runtime_error(SDL_GetError());
    }
}

void Resources::init_values()
{
    screen_w = 1920;
    screen_h = 1080;
    game_running = true;
    game_fullscreen = false;

    color_back = {30, 0, 0, 0};
    color_white = {255, 255, 255, 0};
}

void Resources::init_winren()
{
    window = SDL_CreateWindow(
        "SpaceSurf",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screen_w, screen_h, 0);
    if(!window)
    {
        SDL_Log("Error in creating window");
        throw std::runtime_error(SDL_GetError());
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_ShowCursor(0);
    renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        SDL_Log("Error in creating renderer");
        throw std::runtime_error(SDL_GetError());
    }
}

void Resources::load_fonts()
{
    font_m = TTF_OpenFont("../res/fonts/slkscr.ttf", 32);
}

void Resources::load_textures()
{
    std::vector<std::string> names = {
        "naut1",
        "stone1", "stone2", "stone3", "stone4",
        "surfboard",
    };
    std::vector<std::string> paths = {
        "res/graphics/naut1.png",
        "res/graphics/stones/stone1.png", "res/graphics/stones/stone2.png",
        "res/graphics/stones/stone3.png", "res/graphics/stones/stone4.png",
        "res/graphics/assets/surfboard.png",
    };

    for(unsigned i=0; i<names.size(); ++i)
    {
        SDL_Texture *tex = IMG_LoadTexture(renderer, paths.at(i).c_str());
        if(!tex)
        {
            SDL_Log("Error in loading textures");
            throw std::runtime_error(SDL_GetError());
        }
        all_textures.insert({names.at(i), tex});
    }
}

void Resources::free_fonts()
{
    TTF_CloseFont(font_m);
}

void Resources::free_textures()
{
    for(auto i=all_textures.begin(); i!=all_textures.end(); ++i)
    {
        SDL_DestroyTexture(all_textures.at(i->first));
    }
};

void Resources::free_sdl()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Resources::free_winren()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
