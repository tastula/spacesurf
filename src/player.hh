#ifndef SURF_PLAYER_HH
#define SURF_PLAYER_HH

#include "assets.hh"
#include "clock.hh"
#include "object.hh"
#include <string>
#include <vector>

class Game;
class Resources;

class Player: public GameObject
{
    public:
        Player(Resources& res, Game& game);
        ~Player();
        virtual void init();
        virtual void update(float delta);
        virtual void collide(GameObject& obj);
        virtual void draw();
        float get_velocity();
        void add_general_velocity(float vel);
        void input();
    private:
        float velocity;
        int hit_count;
        Gun gun;
        Surfboard board;
        Clock new_hitlabel;
};

#endif
