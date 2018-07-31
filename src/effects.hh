#ifndef SURF_EFFECTS_HH
#define SURF_EFFECTS_HH

#include "gameobject.hh"
#include "label.hh"
#include "clock.hh"
#include <SDL2/SDL.h>

class Ray: public GameObject
{
    public:
        Ray(Resources& res, Game& game);
        virtual ~Ray();
        virtual void update(float delta);
        virtual SDL_Rect get_hitbox();
    private:
        SDL_Rect area;
};

class HitLabel: public GameObject
{
    public:
        HitLabel(Resources& res, Game& game, std::string hit,
                 float px, float py, float w, float h);
        virtual ~HitLabel();
        virtual void update(float delta);
        virtual void draw();
    private:
        Label label;
        float elapsed_time;
};

class Particle: public GameObject
{
    public:
        Particle(Resources& res, Game& game,
                 int size, float px, float py, float vx, float vy,
                 float lifespan, unsigned color);
        virtual ~Particle();
        virtual void update(float delta) override;
        virtual void draw() override;

    private:
        void check_lifespan(float delta);
        void apply_gravity(float delta);

        unsigned size;
        float elapsed_time;
        float lifespan;
        unsigned color;
        float acceleration = -200;
};

#endif // SURF_EFFECTS_HH
