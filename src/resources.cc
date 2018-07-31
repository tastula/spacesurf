#include "resources.hh"
#include <stdexcept>

constexpr float SCALE = 5;

Resources::Resources()
{
    init_sdl();
    init_values();
    init_winren();
    load_fonts();
    load_textures();
    load_controllers();
}

Resources::~Resources()
{
    free_fonts();
    free_textures();
    free_controllers();
    free_winren();
    free_sdl();
}

void Resources::window_clear()
{
    set_render_color(get_color(COLOR_BACK));
    SDL_RenderClear(renderer);
}

void Resources::set_render_color(SDL_Color* color)
{
    SDL_SetRenderDrawColor(renderer, color->r,color->g,
        color->b, color->a);
}

void Resources::window_draw()
{
    SDL_RenderPresent(renderer);
}

// --- Getters -----------------------------------------------------------------

bool Resources::get_keyboard_key_d(std::string key, int repeat)
{
    if(event.type == SDL_KEYDOWN and event.key.repeat == repeat)
    {
        return (std::string(SDL_GetKeyName(event.key.keysym.sym)) == key);
    }
    return false;
}

bool Resources::get_keyboard_key_u(std::string key, int repeat)
{
    if(event.type == SDL_KEYUP and event.key.repeat == repeat)
    {
        return std::string(SDL_GetKeyName(event.key.keysym.sym)) == key;
    }
    return false;
}

bool Resources::get_controller_button_d(unsigned button)
{
    if(event.type == SDL_CONTROLLERBUTTONDOWN)
    {
        return event.cbutton.button == button;
    }
    return false;
}

bool Resources::get_controller_button_u(unsigned button)
{
    if(event.type == SDL_CONTROLLERBUTTONUP)
    {
        return event.cbutton.button == button;
    }
    return false;
}

SDL_Color* Resources::get_color(unsigned index)
{
    return &all_colors.at(index);
}

// --- Initialization ----------------------------------------------------------

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
    current_naut = int(COLOR_NAUT1);

    all_colors.push_back({255, 255, 255, 0}); // White
    all_colors.push_back({193, 193, 193, 0}); // Grey1 (light)
    all_colors.push_back({140, 140, 140, 0}); // Grey2 (medium)
    all_colors.push_back({100, 100, 100, 0}); // Grey3 (dark)
    all_colors.push_back({0, 0, 0, 0});       // Black
    all_colors.push_back({20, 0, 0, 0});      // Background
    all_colors.push_back({255, 0, 0, 0});     // Red
    all_colors.push_back({0, 255, 0, 0});     // Green
    all_colors.push_back({0, 0, 255, 0});     // Blue
    all_colors.push_back({140, 10, 10, 0});   // Naut 1
    all_colors.push_back({91, 192, 235, 0});  // Confetti 1 (blue jeans)
    all_colors.push_back({235, 231, 76, 0});  // Confetti 2 (gargoyle gas)
    all_colors.push_back({155, 197, 61, 0});  // Confetti 3 (android green)
    all_colors.push_back({229, 89, 52, 0});   // Confetti 4 (flame)
    all_colors.push_back({250, 121, 33, 0});  // Confetti 5 (princeton orange)

    draw_hitbox = false;
}

void Resources::init_winren()
{
    window = SDL_CreateWindow(
        "SpaceSurf",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(!window)
    {
        SDL_Log("Error in creating window");
        throw std::runtime_error(SDL_GetError());
    }
    SDL_ShowCursor(0);
    renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED
        |SDL_RENDERER_TARGETTEXTURE);
    if(!renderer)
    {
        SDL_Log("Error in creating renderer");
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Rect screen_size;
    SDL_RenderGetViewport(renderer, &screen_size);
    screen_w = screen_size.w / SCALE;
    screen_h = screen_size.h / SCALE;

    framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, screen_w, screen_h);
}

// --- Loading -----------------------------------------------------------------

void Resources::load_fonts()
{
    font_s = TTF_OpenFont("res/fonts/slkscr.ttf", 8);
    if(!font_s)
    {
        SDL_Log("Error in loading fonts");
        throw std::runtime_error(SDL_GetError());
    }
    font_m = TTF_OpenFont("res/fonts/slkscr.ttf", 8*2);
    if(!font_m)
    {
        SDL_Log("Error in loading fonts");
        throw std::runtime_error(SDL_GetError());
    }
    font_l = TTF_OpenFont("res/fonts/slkscr.ttf", 8*4);
    if(!font_l)
    {
        SDL_Log("Error in loading fonts");
        throw std::runtime_error(SDL_GetError());
    }
}

void Resources::load_textures()
{
    std::vector<std::string> names = {
        "naut1",
        "head1",
        "stone1", "stone2", "stone3", "stone4",
        "gun", "surfboard"
    };
    std::vector<std::string> paths = {
        "res/graphics/naut1.png",
        "res/graphics/heads/head1.png",
        "res/graphics/stones/stone1.png", "res/graphics/stones/stone2.png",
        "res/graphics/stones/stone3.png", "res/graphics/stones/stone4.png",
        "res/graphics/assets/gun.png", "res/graphics/assets/surfboard.png"
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

void Resources::load_controllers()
{
    controller = nullptr;

    // A controller exists
    if(SDL_NumJoysticks() && SDL_IsGameController(0))
    {
        controller = SDL_GameControllerOpen(0);
        // Could't open
        if(!controller)
        {
            SDL_Log("Error in loading controller");
            throw std::runtime_error(SDL_GetError());
        }
    }
}

// --- Freeing -----------------------------------------------------------------

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
}

void Resources::free_controllers()
{
    // Controller is in use
    if(!controller)
    {
        SDL_GameControllerClose(controller);
    }
}

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
