#include "assets.hh"

// --- Surfboard -----------------------------------------------

Surfboard::Surfboard(Resources& res, std::string tex)
:Object(res, tex)
{
}

Surfboard::~Surfboard()
{
}

void Surfboard::update(float vel, float x, float y)
{
    if(vel > 0) angle = 10;
    else if(vel < 0) angle = -10;
    else angle = 0;

    set_position(x, y);
}

void Surfboard::update(float delta)
{
}

bool Surfboard::remove()
{
    return false;
}
