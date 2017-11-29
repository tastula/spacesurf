#include "object.hh"
#include "resources.hh"

Object::Object(Resources& res)
:res(res)
{
    px = 0;
    py = 0;
    pz = 0;
    vx = 0;
    vy = 0;
    h = 0;
    w = 0;
}

Object::~Object()
{
    // Destructor
}

void Object::add_position(float dx, float dy, float dz)
{
    px += dx;
    py += dy;
    pz += dz;
}

void Object::add_velocity(float dx, float dy)
{
    vx += dx;
    vy += dy;
}

void Object::set_position(float nx, float ny, float nz)
{
    px = nx;
    py = ny;
    pz = nz;
}

void Object::set_velocity(float nx, float ny)
{
    vx = nx;
    vy = ny;
}

float Object::get_px()
{
    return px;
}

float Object::get_py()
{
    return py;
}

float Object::get_vx()
{
    return vx;
}

float Object::get_vy()
{
    return vy;
}
