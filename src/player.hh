#ifndef SURF_PLAYER_HH
#define SURF_PLAYER_HH

#include "assets.hh"
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
        bool remove();
        void input();
        void draw();
    private:
        int velocity;
        Surfboard board;
};

#endif
