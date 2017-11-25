#ifndef SURF_GAME_HH
#define SURF_GAME_HH

#include "clock.hh"
#include "level.hh"
#include "player.hh"
#include <vector>

class Resources;

class Game
{
    public:
        Game(Resources &res);
        ~Game();
        void init();
        void input();
        void update(float delta);
        void draw();
    private:
        void add_rays();
        void update_layer(float delta, std::vector<Object*>& layer);
        void draw_layer(std::vector<Object*>& layer);

        Resources& res;
        Level level;
        Clock new_ray;
};

#endif
