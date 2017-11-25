#ifndef SURF_EFFECTS_HH
#define SURF_EFFECTS_HH

#include "object.hh"

class Resources;

class Ray: public Object
{
    public:
        Ray(Resources& res);
        ~Ray();
        void init();
        void update(float delta);
        void draw();
        bool remove();
    private:
        SDL_Rect area;
};

#endif
