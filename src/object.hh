#ifndef SURF_OBJECT_HH
#define SURF_OBJECT_HH

#include <SDL2/SDL.h>

class Resources;

class Object
{
    public:
        Object(Resources &res, SDL_Texture *tex);
        virtual ~Object();
        virtual void init();
        virtual void draw();

        void add_pos_x(float delta);
        void add_pos_y(float delta);
        void add_vel_x(float delta);
        void add_vel_y(float delta);
        void set_pos_x(float position);
        void set_pos_y(float position);
        void set_vel_x(float position);
        void set_vel_y(float position);
        float get_pos_x();
        float get_pos_y();
        float get_vel_x();
        float get_vel_y();

    private:
        Resources& res;
        SDL_Texture *tex;
        float pos_x;
        float pos_y;
        float vel_x;
        float vel_y;
        int w;
        int h;
        float angle;
};

#endif
