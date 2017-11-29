#include "assets.hh"
#include "game.hh"
#include "resources.hh"

// --- Surfboard ---------------------------------------------------------------

constexpr int BOARD_ANGLE = 10;

Surfboard::Surfboard(Resources& res, Game& game, std::string name)
:GameObject(res, game, name)
{
    // Constructor
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

Gun::Gun(Resources& res, Game& game, std::string name)
:GameObject(res, game, name)
{
    // Constructor
}

Gun::~Gun()
{
    // Destructor
}

void Gun::input()
{
    if(res.get_keyboard_key_d("Space"))
    {
        shoot();
    }
    else if(res.get_controller_button_d(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
    {
        shoot();
    }
}

void Gun::shoot()
{
    Bullet* bullet = new Bullet(res, game, px+w, py);
    game.level_add_object(bullet);
}

void Gun::update(float nx, float ny)
{
    set_position(nx, ny);
}

// --- Bullet ------------------------------------------------------------------

Bullet::Bullet(Resources& res, Game& game, int nx, int ny)
:GameObject(res, game)
{
    px = nx;
    py = ny;
    vx = 200;
    w = 6;
    h = 2;
    power = 1;
    color = &res.color_white;
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
