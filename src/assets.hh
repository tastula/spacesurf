#ifndef SURF_ASSETS_HH
#define SURF_ASSETS_HH

#include "gameobject.hh"
#include <string>

class Resources;

class Surfboard: public GameObject
{
    public:
        Surfboard(Resources& res, Game& game, std::string name);
        virtual ~Surfboard();

        void update(float vy, float nx, float ny);
};
#endif // SURF_ASSETS_HH
