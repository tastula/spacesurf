#include "effects.hh"
#include "resources.hh"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

// --- Ray ---------------------------------------------------------------------

constexpr int RAY_W = 12;
constexpr int RAY_H = 2;
constexpr int RAY_VELOCITY = 320;

Ray::Ray(Resources& res, Game& game)
:GameObject(res, game)
{
    active = false;
    w = RAY_W;
    h = RAY_H;
    collidable = false;
    px = res.screen_w;
    py = rand() % res.screen_h;
    vx = -RAY_VELOCITY;
    area = {int(px), int(py), w, h};
    color = res.get_color(COLOR_WHITE);
}

Ray::~Ray()
{
}

void Ray::update(float delta)
{
    add_position(vx*delta, 0);
    area = {int(px), int(py), w, h};

    if(px < -w)
    {
        finished = true;
    }
}

SDL_Rect Ray::get_hitbox()
{
    return area;
}

// --- HitLabel ----------------------------------------------------------------

constexpr float LIFESPAN = 1.5;
constexpr float VELOCITY_X = 100;
constexpr float VELOCITY_Y = 50;
constexpr float ACCELERATION = -600;

HitLabel::HitLabel(Resources &res, Game &game, std::string hit,
                   float px, float py, float w, float h)
:GameObject(res, game), label(res, hit, res.font_s), elapsed_time(0)
{
    active = false;

    this->px = (w/2)+px;
    this->py = (h/2)+py;
    this->vx = VELOCITY_X;
    // Random between [-VEL_Y, VEL_Y]
    this->vy = (((float) std::rand()/RAND_MAX)-0.5)*VELOCITY_Y;

    label.update_color_main(res.get_color(COLOR_RED));
    label.update_pos(this->px, this->py);
}

HitLabel::~HitLabel()
{
    // Destructor
}

void HitLabel::update(float delta)
{
    elapsed_time += delta;
    if(elapsed_time > LIFESPAN)
    {
        finished = true;
    }

    // Physics yay
    vx += ACCELERATION*delta;
    px += vx*delta;
    py += vy*delta;
}

void HitLabel::draw()
{
    label.draw_center(px, py);
}

// --- Particle ----------------------------------------------------------------

Particle::Particle(Resources &res, Game &game,
                   int size, float px, float py, float vx, float vy,
                   float lifespan, unsigned color)
: GameObject(res, game), size(size), lifespan(lifespan), color(color)
{
    this->px = px;
    this->py = py;
    this->vx = vx;
    this->vy = vy;
}

Particle::~Particle()
{
    // Pass
}

void Particle::update(float delta)
{
    this->add_position(vx*delta, vy*delta);
    check_lifespan(delta);
    apply_gravity(delta);
}

void Particle::draw()
{
    SDL_Rect rect = {int(px), int(py), int(size), int(size)};
    res.set_render_color(res.get_color(color));
    SDL_RenderFillRect(res.renderer, &rect);
}

void Particle::check_lifespan(float delta)
{
    elapsed_time += delta;
    if(elapsed_time > lifespan)
    {
        finished = true;
    }
}

void Particle::apply_gravity(float delta)
{
    this->add_velocity(acceleration*delta, 0);
    this->add_position(vx*delta, vy*delta);
}
