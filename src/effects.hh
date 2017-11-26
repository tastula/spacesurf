#ifndef SURF_EFFECTS_HH
#define SURF_EFFECTS_HH

#include "object.hh"

class Resources;

class Ray: public Object
{
    public:
        Ray(Resources& res);
        ~Ray();
        virtual void init();
        virtual void update(float delta);
        virtual void draw();
        virtual bool remove();
    private:
        SDL_Rect area;
};

#endif
