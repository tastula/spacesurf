#include "object.hh"
#include "resources.hh"

Object::Object(Resources& res, SDL_Texture *tex)
:res(res), tex(tex)
{
    init();
}

Object::~Object()
{
}

void Object::init()
{
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    angle = 0;
}

void Object::draw()
{
    SDL_Rect dts = {int(pos_x), int(pos_y), w, h};
    SDL_RenderCopyEx(res.renderer, tex, NULL, &dts, int(angle), NULL,
                     SDL_FLIP_NONE);
}

void Object::add_pos_x(float delta)
{
    pos_x += delta;
}

void Object::add_pos_y(float delta)
{
    pos_y += delta;
}

void Object::add_vel_x(float delta)
{
    vel_x += delta;
}

void Object::add_vel_y(float delta)
{
    vel_y += delta;
}

void Object::set_pos_x(float position)
{
    pos_x = position;
}

void Object::set_pos_y(float position)
{
    pos_y = position;
}

void Object::set_vel_x(float position)
{
    vel_x = position;
}

void Object::set_vel_y(float position)
{
    vel_y = position;
}

float Object::get_pos_x()
{
    return pos_x;
}

float Object::get_pos_y()
{
    return pos_y;
}

float Object::get_vel_x()
{
    return vel_x;
}

float Object::get_vel_y()
{
    return vel_y;
}
