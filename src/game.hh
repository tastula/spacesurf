#ifndef SURF_GAME_HH
#define SURF_GAME_HH

#include "clock.hh"
#include "player.hh"

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
        void update_rays();
        void update_layers(float delta);
        void draw_layers();

        Resources& res;
        Player player;

        Clock new_ray;
};

#endif
