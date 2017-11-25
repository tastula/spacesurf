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
        std::string get_pressed_key(int repeat=0);
        std::string get_released_key(int repeat=0);

        int screen_w;
        int screen_h;

        bool game_running;
        bool game_fullscreen;
        bool game_paused;

        SDL_Window* window;
        SDL_Renderer* renderer;

        SDL_Color color_back;
        SDL_Color color_white;

        SDL_Event event;
        TTF_Font *font_m;

        map_texture all_textures;

        std::vector<Object*> layer1;
        std::vector<Object*> layer2;
    private:
        void init_sdl();
        void init_values();
        void init_winren();
        void load_fonts();
        void load_textures();
        void free_fonts();
        void free_textures();
        void free_sdl();
        void free_winren();
};

#endif
