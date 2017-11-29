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
    velocity = 160;
    health = 600;
}

void Player::update(float delta)
{
    add_position(vx*delta, vy*delta);

    // Keep the player on screen
    if(px < 0) px = 0;
    else if(px > res.screen_w-w) px = res.screen_w-w;
    if(py < 0) py = 0;
    else if(py > res.screen_h-h) py = res.screen_h-h;
    
    gun.update(px+w, py+5);
    board.update(vy, px-2, py+h-3);

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
    if(res.get_keyboard_key_d("W")) vy -= velocity;
    if(res.get_keyboard_key_d("S")) vy += velocity;
    if(res.get_keyboard_key_d("A")) vx -= velocity;
    if(res.get_keyboard_key_d("D")) vx += velocity;

    if(res.get_keyboard_key_u("W")) vy += velocity;
    if(res.get_keyboard_key_u("S")) vy -= velocity;
    if(res.get_keyboard_key_u("A")) vx += velocity;
    if(res.get_keyboard_key_u("D")) vx -= velocity;

    if(res.event.type == SDL_CONTROLLERAXISMOTION)
    {
        float division = 32767/velocity;
        if(res.event.caxis.axis == 0) vx = res.event.caxis.value/division;
        if(res.event.caxis.axis == 1) vy = res.event.caxis.value/division;
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
