#include "game.hh"
#include "player.hh"
#include "resources.hh"
#include <string>

Player::Player(Resources &res, Game& game, std::string name)
:GameObject(res, game, name), gun(res, game, "gun"),
 board(res, game, "surfboard")
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
    add_position(vx*delta, vy*delta);

    // Keep the player on screen
    // TODO: Remove offsets when pictures are fixed
    if(px < 10) px = 10;
    else if(px > res.screen_w-w+20) px = res.screen_w-w+20;
    if(py < -10) py = -10;
    else if(py > res.screen_h-h-10) py = res.screen_h-h-10;
    
    gun.update(px+70, py+45);
    board.update(vy, px-10, py+55);

    // Just to toggle playing and death
    remove();
}

void Player::draw()
{
    if(game.is_playing())
    {
        gun.draw();
        board.draw();
        GameObject::draw();
    }
}


bool Player::remove()
{
    if(health <= 0)
    {
        game.play(false);
        return true;
    }
    return false;
}

void Player::input()
{
    std::string key = res.get_pressed_key();
    if(key != "")
    {
        if(key == "W") vy -= velocity;
        if(key == "S") vy += velocity;
        if(key == "A") vx -= velocity;
        if(key == "D") vx += velocity;
    }
    key = res.get_released_key();
    if(key != "")
    {
        if(key == "W") vy += velocity;
        if(key == "S") vy -= velocity;
        if(key == "A") vx += velocity;
        if(key == "D") vx -= velocity;
    }

    gun.input();
}

void Player::collide(GameObject& obj)
{
    health -= obj.get_power();
    if(health < 0)
    {
        health = 0;
    }
}
