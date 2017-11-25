#include "player.hh"
#include "resources.hh"
#include <string>

Player::Player(Resources &res, std::string tex)
:Object(res, tex), board(res, "surfboard")
{
    init();
}

Player::~Player()
{
}

void Player::init()
{
    velocity = 600;
    health = 600;
}

void Player::update(float delta)
{
    add_pos_x(vel_x*delta);
    add_pos_y(vel_y*delta);

    // Keep the player on screen
    // TODO: Remove offsets when pictures are fixed
    if(pos_x < 10) pos_x = 10;
    else if(pos_x > res.screen_w-w+20) pos_x = res.screen_w-w+20;
    if(pos_y < -10) pos_y = -10;
    else if(pos_y > res.screen_h-h-10) pos_y = res.screen_h-h-10;
    
    board.update(vel_y, pos_x-10, pos_y+55);
}

void Player::draw()
{
    board.draw();
    Object::draw();
}


bool Player::remove()
{
    return health < 0;
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
