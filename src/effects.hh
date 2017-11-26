#ifndef SURF_EFFECTS_HH
#define SURF_EFFECTS_HH

#include "object.hh"
#include <SDL2/SDL.h>

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
        virtual SDL_Rect get_hitbox();
    private:
        SDL_Rect area;
};

#endif
