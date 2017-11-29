#ifndef SURF_PLAYER_HH
#define SURF_PLAYER_HH

#include "assets.hh"
#include "object.hh"
#include <string>

class Game;
class Resources;

class Player: public GameObject
{
    public:
        Player(Resources& res, Game& game, std::string name);
        ~Player();
        virtual void init();
        virtual void update(float delta);
        virtual bool remove();
        virtual void collide(GameObject& obj);
        virtual void draw();
        void input();
    private:
        int velocity;
        Gun gun;
        Surfboard board;
};

#endif
