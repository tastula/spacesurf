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
        virtual void add_position(float dx, float dy, float dz = 0) override;
        virtual void set_position(float nx, float ny, float nz = 0) override;
        float get_velocity();
        void set_skills();
        void add_general_velocity(float vel);
        void input();
    private:
        float velocity;
        int hit_count;
        Game& game;
        Gun gun;
        Surfboard board;
        Clock new_hitlabel;
};

#endif
