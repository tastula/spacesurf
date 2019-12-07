#ifndef SURF_DIALOGUE_HH
#define SURF_DIALOGUE_HH

#include "gameobject.hh"
#include <cstdlib>

class Game;
class Resources;

class Stone: public GameObject
{
    public:
        Stone(Resources& res, Game& game, int size=rand()%4, float vy=0);
        ~Stone();
        
        virtual void init();
        virtual void update(float delta);
        virtual void collide(GameObject &obj);
        void split();
    private:
        Game& game;
        bool shot;
        int size;
        int rotation;
};

#endif
