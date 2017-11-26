#ifndef SURF_OBJECT_HH
#define SURF_OBJECT_HH

#include <SDL2/SDL.h>
#include <string>

class Resources;

class Object
{
    public:
        Object(Resources &res, std::string tex);
        Object(Resources &res);
        virtual ~Object();
        virtual void init();
        virtual bool remove();
        virtual void update(float delta) = 0;
        virtual void draw();
        virtual void collide(Object& obj);
        virtual SDL_Rect get_hitbox();

        void set_texture(std::string tex);
        void set_texture(SDL_Texture *tex);
        void add_pos_x(float delta);
        void add_pos_y(float delta);
        void add_vel_x(float delta);
        void add_vel_y(float delta);
        void set_position(float new_x, float new_y);
        void set_pos_x(float position);
        void set_pos_y(float position);
        void set_vel_x(float position);
        void set_vel_y(float position);
        float get_pos_x();
        float get_pos_y();
        float get_vel_x();
        float get_vel_y();
        bool get_against();
        int get_power();
        int get_health();

    protected:
        Resources& res;
        SDL_Texture *tex;
        // TODO: use matrixes B)
        float pos_x;
        float pos_y;
        float vel_x;
        float vel_y;
        int w;
        int h;
        float angle;
        bool finished;
        bool collidable;
        bool against_player;

        int health;
        int power;
};

#endif
