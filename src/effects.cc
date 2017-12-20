#include "effects.hh"
#include "resources.hh"
#include <SDL2/SDL.h>

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
constexpr float VELOCITY = -120;
constexpr float ACCELERATION = 300;

HitLabel::HitLabel(Resources &res, Game &game, std::string hit,
                   float px, float py, float w, float h)
:GameObject(res, game), label(res, hit, res.font_m)
{
    active = false;

    this->px = (w/2)+px;
    this->py = (h/2)+py;
    this->vy = VELOCITY;

    label.update_color_main(res.get_color(COLOR_RED));
    label.update_pos(this->px, this->py);
    destruction.restart();
}

HitLabel::~HitLabel()
{
    // Destructor
}

void HitLabel::update(float delta)
{
    elapsed_time += delta;
    if(destruction.time() > LIFESPAN)
    {
        finished = true;
    }

    // Physics yay
    vy += ACCELERATION*delta;
    py += vy*delta;
}

void HitLabel::draw()
{
    label.draw_center(px, py);
}
