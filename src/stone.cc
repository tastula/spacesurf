#include "resources.hh"
#include "stone.hh"
#include "game.hh"
#include <string>

Stone::Stone(Resources& res, Game& game, int size, float vel_y)
:GameObject(res, game), size(size+1)
{
    Stone::init();
    vy = vel_y;
}

Stone::~Stone()
{
    //SDL_Log("Stone now gone");
}

void Stone::init()
{
    std::string name = "stone"+std::to_string(size);
    GameObject::set_texture(name);
    px = res.screen_w + rand()%6;
    py = rand()%res.screen_h - h/2;
    vx = -(72 + rand()%(size*40));
    shot = false;
    power = 1;
    against_player = true;
    // Always positive
    rotation = -vx;
}

void Stone::update(float delta)
{
    add_position(vx*delta, vy*delta);
    angle -= rotation*delta;

    // Stone out of range
    if(px < -w)
    {
        finished = true;
    }

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
    if(shot)
    {
        if(size < 4)
        {
            // Ugly af copy-paste code
            Stone *new_stone = new Stone(res, game, size, 24);
            new_stone->set_position(px, py+w-new_stone->get_w());
            game.get_level()->add_object(new_stone);
            new_stone = new Stone(res, game, size, -24);
            new_stone->set_position(px, py);
            game.get_level()->add_object(new_stone);
        }
        // Bye bye stone
        finished = true;
    }
}
