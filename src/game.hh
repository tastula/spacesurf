#ifndef SURF_GAME_HH
#define SURF_GAME_HH

#include "clock.hh"
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
        void add_stones();
        void update_layer(float delta, std::vector<Object*>& layer);
        void draw_layer(std::vector<Object*>& layer);

        Resources& res;
        Player player;

        Clock new_ray;
        Clock new_stone;
};

#endif
