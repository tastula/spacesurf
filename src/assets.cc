#include "assets.hh"
#include "game.hh"
#include "resources.hh"

// --- Surfboard ---------------------------------------------------------------

constexpr int BOARD_ANGLE = 10;

Surfboard::Surfboard(Resources& res, std::string name)
:GameObject(res, name)
{
    active = false;
}

Surfboard::~Surfboard()
{
    // Destructor
}

void Surfboard::update(float vy, float nx, float ny)
{
    if(vy != 0)
    {
        angle = BOARD_ANGLE*vy/abs(vy);
    }
    else
    {
        angle = 0;
    }

    set_position(nx, ny);
}

// --- Gun ---------------------------------------------------------------------

constexpr float BULLET_TIME = 0.3;

Gun::Gun(Resources& res, Game& game, std::string name)
:GameObject(res, name), game(game)
{
    active = false;
    shooting = false;
    new_bullet.restart();
}

Gun::~Gun()
{
    // Destructor
}

void Gun::shoot()
{
    Bullet* bullet = new Bullet(res, px+w, py);
    game.get_level()->add_object(bullet);
}

void Gun::update(float nx, float ny)
{
    set_position(nx, ny);

    if(shooting && new_bullet.time() > BULLET_TIME && game.is_playing())
    {
        shoot();
        new_bullet.restart();
    }
}

void Gun::input()
{
    if(res.get_keyboard_key_d("Space"))
    {
        shooting = true;
    }
    else if(res.get_keyboard_key_u("Space"))
    {
        shooting = false;
    }

    if(res.get_controller_button_d(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
    {
        shooting = true;
    }
    else if(res.get_controller_button_u(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
    {
        shooting = false;
    }
}

// --- Bullet ------------------------------------------------------------------

Bullet::Bullet(Resources& res, int nx, int ny)
:GameObject(res)
{
    px = nx;
    py = ny;
    vx = 260;
    w = 6;
    h = 2;
    power = 1;
    color = res.get_naut_color();
}

Bullet::~Bullet()
{
    // Destructor
}

void Bullet::collide(GameObject& obj)
{
    // Bullet did some damage (hopefully)
    if(obj.get_against())
    {
        finished = true;
        power = 0;
    }
}

void Bullet::update(float delta)
{
    add_position(vx*delta, vy*delta);

    if(px > res.screen_w)
    {
        finished = true;
    }
}
