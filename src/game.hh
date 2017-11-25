#ifndef SURF_GAME_HH
#define SURF_GAME_HH

#include "label.hh"

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
        Resources& res;
        Label test;
};

#endif
