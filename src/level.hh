#ifndef SURF_LEVEL_HH
#define SURG_LEVEL_HH

#include "clock.hh"
#include "player.hh"

class Resources;

class Level
{
    public:
        Level(Resources& res);
        ~Level();
        void init();
        void input();
        void update(float delta);
        void draw();

        // TODO: A ton of congigurations ad tweaking, this is the place
        // TODO: Read levels from a file, clocks with callbacks?

    private:
        void add_stones();

        Resources& res;
        Player* player;
        Clock new_stone;
};

#endif
