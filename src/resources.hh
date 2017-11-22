#ifndef SURF_RESOURCES_HH
#define SURF_RESOURCES_HH

#include <SDL2/SDL.h>

class Resources
{
    public:
        Resources();
        ~Resources();
        // Working with window
        void window_clear();
        void window_draw();

        int screen_w;
        int screen_h;

        bool game_running;

        SDL_Window* window;
        SDL_Renderer* renderer;

    private:
        void init_sdl();
        void init_values();
        void init_winren();
};

#endif
