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
}

Ray::~Ray()
{
}

void Ray::update(float delta)
{
    add_position(vx*delta, 0);
    area = {int(px), int(py), w, h};
}

void Ray::draw()
{
    SDL_SetRenderDrawColor(res.renderer, res.color_white.r,
        res.color_white.g, res.color_white.b, res.color_white.a);
    SDL_RenderFillRect(res.renderer, &area);
    SDL_SetRenderDrawColor(res.renderer, res.color_back.r,
        res.color_back.g, res.color_back.b, res.color_back.a);
}

bool Ray::remove()
{
    if(px < -w)
    {
        return true;
    }
    return false;
}

SDL_Rect Ray::get_hitbox()
{
    return area;
}
