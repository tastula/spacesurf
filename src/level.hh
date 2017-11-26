#ifndef SURF_LEVEL_HH
#define SURG_LEVEL_HH

#include "clock.hh"
#include "label.hh"
#include "player.hh"

class Object;
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
        void handle_collision(Object& o1, Object& o2);

        // TODO: A ton of congigurations ad tweaking, this is the place
        // TODO: Read levels from a file, clocks with callbacks?

    private:
        void add_stones();

        Resources& res;
        Player* player;
        Clock new_stone;
        Label hp;
};

#endif
