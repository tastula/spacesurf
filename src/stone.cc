#include "resources.hh"
#include "stone.hh"
#include "game.hh"
#include <string>

Stone::Stone(Resources& res, Game& game, int size, float vel_y)
:GameObject(res, game), size(size+1)
{
    Stone::init();
    this->vy = vel_y;
}

Stone::~Stone()
{
    //SDL_Log("Stone now gone");
}

void Stone::init()
{
    std::string name = "stone"+std::to_string(size);
    GameObject::set_texture(name);
    px = res.screen_w + rand()%30;
    py = rand()%res.screen_h - h/2;
    vx = -(360 + rand()%(size*200));
    shot = false;
    power = 1;
    against_player = true;
    // Always positive
    rotation = -2*(vx/10);
}

void Stone::update(float delta)
{
    add_position(vx*delta, vy*delta);
    angle -= rotation*delta;
    split();
}

void Stone::collide(GameObject &obj)
{
    if(obj.get_power() > 0)
    {
        shot = true;
    }
}

void Stone::split()
{
    // Time for baby stones
    if(size < 4 and shot > 1)
    {
        // Ugly af copy-paste code
        Stone *new_stone = new Stone(res, game, size+1, 120+rand()%80);
        new_stone->set_position(px, py);
        game.level_add_stone(new_stone);
        new_stone = new Stone(res, game, size+1, -(120+rand()%80));
        new_stone->set_position(px, py);
        game.level_add_stone(new_stone);
        
        // Bye bye stone
        finished = true;
    }
}

bool Stone::remove()
{
    if(px < -h)
    {
        finished = true;
    }
    return finished;
}
