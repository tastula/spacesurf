#include "resources.hh"
#include "stone.hh"
#include <string>

Stone::Stone(Resources& res, int size, float vel_y)
:Object(res), size(size)
{
    init();
    this->vel_y = vel_y;
}

Stone::~Stone()
{
}

void Stone::init()
{
    tex = res.all_textures.at(("stone"+std::to_string(size)).c_str());
    pos_x = res.screen_w + rand()%30;
    pos_y = rand()%res.screen_h - h/2;
    vel_x = 350 + rand()%(size*50);
}

void Stone::update(float delta)
{
    add_pos_x(vel_x*delta);
    add_pos_y(vel_y*delta);
    split();
}

void Stone::split()
{
    // Time for baby stones
    if(size < 4 and shot > 1)
    {
        // Ugly af copy-paste code
        Stone *new_stone = new Stone(res, size+1, 120+rand()%80);
        new_stone->set_position(pos_x, pos_y);
        res.layer1.emplace_back(new_stone);
        new_stone = new Stone(res, size+1, -(120+rand()%80));
        new_stone->set_position(pos_x, pos_y);
        res.layer1.emplace_back(new_stone);
        
        // Bye bye stone
        finished = true;
    }
}

bool Stone::remove()
{
    if(pos_x < -h)
    {
        finished = true;
    }
    return finished;
}
