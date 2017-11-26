#include "effects.hh"
#include "resources.hh"
#include <SDL2/SDL.h>

// --- Ray -------------------------------------

Ray::Ray(Resources& res)
:Object(res)
{
    Ray::init();
}

Ray::~Ray()
{
}

void Ray::init()
{
    w = 60;
    h = 10;
    collidable = false;
    pos_x = res.screen_w;
    pos_y = rand() % res.screen_h;
    vel_x = -1600;
    area = {int(pos_x), int(pos_y), w, h};
}

void Ray::update(float delta)
{
    add_pos_x(vel_x*delta);
    area = {int(pos_x), int(pos_y), w, h};
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
    if(pos_x < -w)
    {
        return true;
    }
    return false;
}

SDL_Rect Ray::get_hitbox()
{
    return area;
}
