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
        void set_render_color(SDL_Color* color);

        // Events
        SDL_Event event;
        bool get_keyboard_key_u(std::string key, int repeat=0);
        bool get_keyboard_key_d(std::string key, int repeat=0);
        bool get_controller_button_u(unsigned button);
        bool get_controller_button_d(unsigned button);

        SDL_Color* get_color(unsigned index);

        int screen_w;
        int screen_h;

        int current_naut;

        SDL_Window* window;
        SDL_Renderer* renderer;

        SDL_GameController* controller;
        TTF_Font *font_s;
        TTF_Font *font_m;
        TTF_Font *font_l;

        // Setting, load from file
        // Can be turned into map maybe?
        bool draw_hitbox;

        SDL_Texture* framebuffer;

        map_texture all_textures;
        std::vector<SDL_Color> all_colors;
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

enum colors
{
    COLOR_WHITE = 0,
    COLOR_GREY1,
    COLOR_GREY2,
    COLOR_GREY3,
    COLOR_BLACK,
    COLOR_BACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_NAUT1,
    //COLOR_NAUT2,
    //COLOR_NAUT3,
    //COLOR_NAUT4,
    COLOR_CONFETTI1,
    COLOR_CONFETTI2,
    COLOR_CONFETTI3,
    COLOR_CONFETTI4,
    COLOR_CONFETTI5
};

enum game_state
{
    STATE_MENU = 0,
    STATE_GAME
};

enum menus
{
    MENU_MAIN = 0,
    MENU_OPTIONS
};

#endif
