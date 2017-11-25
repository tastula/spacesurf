#ifndef SURF_PLAYER_HH
#define SURF_PLAYER_HH

#include "object.hh"

class Resources;

class Player: public Object
{
    public:
        Player(Resources& res);
        ~Player();
        void init();
        void update(float delta);
        void input();
};

#endif
