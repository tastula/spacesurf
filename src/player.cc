#include "player.hh"
#include "resources.hh"
#include <string>

Player::Player(Resources &res, std::string tex)
:Object(res, tex)
{
    init();
}

Player::~Player()
{
}

void Player::init()
{
    velocity = 400;
}

void Player::update(float delta)
{
    add_pos_x(vel_x*delta);
    add_pos_y(vel_y*delta);
}

void Player::input()
{
    if(res.event.type == SDL_KEYDOWN and res.event.key.repeat == 0)
    {
        std::string key = SDL_GetKeyName(res.event.key.keysym.sym);
        if(key == "W") vel_y -= velocity;
        if(key == "S") vel_y += velocity;
        if(key == "A") vel_x -= velocity;
        if(key == "D") vel_x += velocity;
    }
    else if(res.event.type == SDL_KEYUP && res.event.key.repeat == 0)
    {
        std::string key = SDL_GetKeyName(res.event.key.keysym.sym);
        if(key == "W") vel_y += velocity;
        if(key == "S") vel_y -= velocity;
        if(key == "A") vel_x += velocity;
        if(key == "D") vel_x -= velocity;
    }
}
