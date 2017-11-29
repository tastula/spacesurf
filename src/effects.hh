#ifndef SURF_EFFECTS_HH
#define SURF_EFFECTS_HH

#include "gameobject.hh"
#include <SDL2/SDL.h>

class Ray: public GameObject
{
    public:
        Ray(Resources& res, Game& game);
        ~Ray();
        virtual void update(float delta);
        virtual void draw();
        virtual bool remove();
        virtual SDL_Rect get_hitbox();
    private:
        SDL_Rect area;
};

#endif // SURF_EFFECTS_HH
