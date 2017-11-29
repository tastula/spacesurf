#include "effects.hh"
#include "resources.hh"
#include <SDL2/SDL.h>

// --- Ray ---------------------------------------------------------------------

constexpr int RAY_W = 60;
constexpr int RAY_H = 10;

Ray::Ray(Resources& res, Game& game)
:GameObject(res, game)
{
    w = RAY_W;
    h = RAY_H;
    collidable = false;
    px = res.screen_w;
    py = rand() % res.screen_h;
    vx = -1600;
    area = {int(px), int(py), w, h};
    color = &res.color_white;
}

Ray::~Ray()
{
}

void Ray::update(float delta)
{
    add_position(vx*delta, 0);
    area = {int(px), int(py), w, h};

    if(px < -w)
    {
        finished = true;
    }
}

SDL_Rect Ray::get_hitbox()
{
    return area;
}
