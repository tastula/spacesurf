#include "object.hh"
#include "resources.hh"

Object::Object(Resources& res, std::string tex)
:res(res)
{
    init();
    set_texture(tex);
}

Object::Object(Resources& res)
:res(res)
{
    // There's no texture yet, create one asap!
    // Remember to manually set the texture.
    init();
}

Object::~Object()
{
}

void Object::init()
{
    pos_x = 0;
    pos_y = 0;
    vel_x = 0;
    vel_y = 0;
    h = 0;
    w = 0;
    angle = 0;
    health = 1;
    finished = false;
}

void Object::draw()
{
    SDL_Rect dts = {int(pos_x), int(pos_y), w, h};
    SDL_RenderCopyEx(res.renderer, tex, NULL, &dts, int(angle), NULL,
                     SDL_FLIP_NONE);
}

void Object::set_texture(std::string tex)
{
    this->tex = res.all_textures.at(tex);
    SDL_QueryTexture(this->tex, NULL, NULL, &w, &h);
}

void Object::set_texture(SDL_Texture *tex)
{
    this->tex = tex;
    SDL_QueryTexture(this->tex, NULL, NULL, &w, &h);
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

void Object::set_position(float new_x, float new_y)
{
    set_pos_x(new_x);
    set_pos_y(new_y);
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

bool Object::remove()
{
    // Remove if there's no health
    return !health;
}
