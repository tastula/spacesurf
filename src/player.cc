#include "game.hh"
#include "effects.hh"
#include "player.hh"
#include "resources.hh"
#include <string>

constexpr float HITLABEL_TIME = 0.1;

// Texture has to be set later
Player::Player(Resources &res, Game& game)
:GameObject(res), game(game), gun(res, game, "gun"),
 board(res, "surfboard")
{
    Player::init();
}

Player::~Player()
{
}

void Player::init()
{
    set_skills();
    set_texture(res.get_naut_texture());
    new_hitlabel.restart();
    hit_count = 0;
    update(0);
}

void Player::set_skills()
{
    auto skills = res.get_naut_skills();
    velocity = skills.at("speed");
    health = skills.at("health");
}

void Player::update(float delta)
{
    if(active)
    {
        add_position(vx*delta, vy*delta);

        // Keep the player on screen
        if(px < 0) px = 0;
        else if(px > res.screen_w-w) px = res.screen_w-w;
        if(py < 0) py = 0;
        else if(py > res.screen_h-h) py = res.screen_h-h;
    }

    gun.update(px+w, py+5);
    board.update(vy, px-2, py+h-3);

    if(health <= 0)
    {
        game.play(false);
        set_active(false);
        game.get_level()->lose();
    }
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

void Player::input()
{
    if(res.get_keyboard_key_d("W")) vy -= velocity;
    else if(res.get_keyboard_key_u("W")) vy += velocity;

    if(res.get_keyboard_key_d("S")) vy += velocity;
    else if(res.get_keyboard_key_u("S")) vy -= velocity;

    if(res.get_keyboard_key_d("A")) vx -= velocity;
    else if(res.get_keyboard_key_u("A")) vx += velocity;

    if(res.get_keyboard_key_d("D")) vx += velocity;
    else if(res.get_keyboard_key_u("D")) vx -= velocity;

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
    int objpwr = obj.get_power();
    if(objpwr > 0)
    {
        health -= objpwr;
        hit_count += objpwr;
        if(new_hitlabel.time() > HITLABEL_TIME)
        {
            HitLabel* hl = new HitLabel(res, std::to_string(hit_count),
                                        px, py, w, h);
            game.get_level()->add_object(hl);
            hit_count = 0;
            new_hitlabel.restart();
        }
    }
    if(health < 0)
    {
        health = 0;
    }
}

float Player::get_velocity()
{
    return velocity;
}

void Player::add_general_velocity(float vel)
{
    velocity += vel;
}

void Player::add_position(float dx, float dy, float dz) {
    Object::add_position(dx, dy, dz);
    gun.add_position(dx, dy, dz);
    board.add_position(dx, dy, dz);
}

void Player::set_position(float dx, float dy, float dz) {
    Object::set_position(dx, dy, dz);
    gun.set_position(dx+w, dy+5, dz);
    board.set_position(dx-2, dy+h-3, dz);
}