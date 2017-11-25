#ifndef SURF_STONE_HH
#define SURF_STONE_HH

#include "object.hh"
#include <cstdlib>

class Resources;

class Stone: public Object
{
    public:
        Stone(Resources& res, int size=rand()%4, float vel_y=0);
        ~Stone();
        
        void init();
        void update(float delta);
        void split();
        bool remove();
    private:
        int size;
        int shot;
};

#endif
