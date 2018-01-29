#ifndef SURF_GAME_HH
#define SURF_GAME_HH

#include "clock.hh"
#include "level.hh"
#include "menu.hh"
#include "player.hh"
#include <vector>

class Resources;
class Stone;

class Game
{
    public:
        Game(Resources &res);
        Game(const Game& other) = delete;
        ~Game();
        void init();
        void input();
        void update(float delta);
        void draw();
        void play(bool p = true);

        bool is_running();
        bool is_playing();
        bool is_paused();

        Level* get_level();
    private:
        void quit();
        void pause();
        void add_rays();
        void change_menu(unsigned menu);
        void change_state(game_state state);

        Resources& res;
        Level level;

        bool running;
        bool playing;
        bool paused;
        
        Clock new_ray;
        std::vector<GameObject*> layer_effects;

        std::vector<Menu*> menus;
        std::vector<Label*> labels;
        Menu* current_menu;
        game_state state;
};

#endif
