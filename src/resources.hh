#ifndef SURF_RESOURCES_HH
#define SURF_RESOURCES_HH

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Resources
{
    public:
        Resources();
        ~Resources();
        void window_clear();
        void window_draw();

        int screen_w;
        int screen_h;

        bool game_running;

        SDL_Window* window;
        SDL_Renderer* renderer;

        SDL_Color color_back;
        SDL_Color color_white;

        SDL_Event event;
        TTF_Font *font_m;
    private:
        void init_sdl();
        void init_values();
        void init_winren();
        void load_fonts();
        void free_sdl();
        void free_winren();
};

#endif
