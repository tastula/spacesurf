#ifndef SURF_PLAYER_HH
#define SURF_PLAYER_HH

#include "object.hh"
#include <string>

class Resources;

class Player: public Object
{
    public:
        Player(Resources& res, std::string tex);
        ~Player();
        void init();
        void update(float delta);
        void input();
    private:
        int velocity;
};

#endif
