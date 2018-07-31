#ifndef SURF_HUD_HH
#define SURF_HUD_HH

#include "label.hh"
#include "resources.hh"
#include <SDL2/SDL.h>

class HUD
{
    public:
        HUD(Resources& res, float time_max = 15);
        ~HUD();
        void init();
        void update(float delta, int hp);
        void draw();

        void set_time(float time);

    private:
        Resources& res;
        Label health;
        Label time;
        SDL_Texture* tex;
        float time_max;
        float time_elapsed;
        float x_left;
        float x_right;
        float x_now;
        int w, h;
};

#endif
