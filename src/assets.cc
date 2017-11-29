#include "assets.hh"

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
