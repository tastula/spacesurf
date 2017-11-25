#ifndef SURF_ASSETS_HH
#define SURF_ASSETS_HH

#include "object.hh"
#include <string>

class Resources;

class Surfboard: public Object
{
    public:
        Surfboard(Resources& res, std::string tex);
        ~Surfboard();
        void update(float vel, float x, float y);
        void update(float delta);
        bool remove();
};
#endif
