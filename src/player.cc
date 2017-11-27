#include "player.hh"
#include "resources.hh"
#include <string>

Player::Player(Resources &res, std::string tex)
:Object(res, tex), board(res, "surfboard")
{
    Player::init();
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

    // Just to toggle playing and death
    remove();
}

void Player::draw()
{
    if(res.game_playing)
    {
        board.draw();
        Object::draw();
    }
}


bool Player::remove()
{
    if(health <= 0)
    {
        res.game_playing = false;
        return true;
    }
    return false;
}

void Player::input()
{
    std::string key = res.get_pressed_key();
    if(key != "")
    {
        if(key == "W") vel_y -= velocity;
        if(key == "S") vel_y += velocity;
        if(key == "A") vel_x -= velocity;
        if(key == "D") vel_x += velocity;
    }
    key = res.get_released_key();
    if(key != "")
    {
        if(key == "W") vel_y += velocity;
        if(key == "S") vel_y -= velocity;
        if(key == "A") vel_x += velocity;
        if(key == "D") vel_x -= velocity;
    }
}

void Player::collide(Object& obj)
{
    health -= obj.get_power();
    if(health < 0)
    {
        health = 0;
    }
}
