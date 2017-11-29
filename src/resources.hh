#ifndef SURF_RESOURCES_HH
#define SURF_RESOURCES_HH

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

using map_texture = std::map<std::string, SDL_Texture*>;

class Object;

class Resources
{
    public:
        Resources();
        ~Resources();
        void window_clear();
        void window_draw();

        // Events
        SDL_Event event;
        bool get_keyboard_key_u(std::string key, int repeat=0);
        bool get_keyboard_key_d(std::string key, int repeat=0);
        bool get_controller_button_u(unsigned button);
        bool get_controller_button_d(unsigned button);

        int screen_w;
        int screen_h;


        SDL_Window* window;
        SDL_Renderer* renderer;

        SDL_Color color_back;
        SDL_Color color_white;

        SDL_GameController* controller;
        TTF_Font *font_m;


        map_texture all_textures;
    private:
        void init_sdl();
        void init_values();
        void init_winren();

        void load_fonts();
        void load_textures();
        void load_controllers();

        void free_fonts();
        void free_textures();
        void free_controllers();
        void free_sdl();
        void free_winren();
};

#endif
