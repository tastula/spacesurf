#include "gameobject.hh"
#include "resources.hh"
#include <stdexcept>

GameObject::GameObject(Resources& res, std::string name)
:Object(res)
{
    set_texture(name);
    GameObject::init();
}

GameObject::GameObject(Resources &res)
:Object(res)
{
    tex = nullptr;
    init();
}

GameObject::~GameObject()
{
    // Destructor
}

void GameObject::init()
{
    active = true;
    finished = false;
    collidable = true;
    against_player = false;
    angle = 0;
    health = 1;
    power = 0;
    color = nullptr;
}

void GameObject::draw()
{
    SDL_Rect dst = {int(px), int(py), w, h};

    // Draw the texture
    if(tex)
    {
        SDL_RenderCopyEx(res.renderer, tex, NULL, &dst, int(angle),
            NULL, SDL_FLIP_NONE);
        if(res.draw_hitbox)
        {
            res.set_render_color(res.get_color(COLOR_WHITE));
            SDL_RenderDrawRect(res.renderer, &dst);
        }
    }
    // Draw a rectangle
    else if(color)
    {
        res.set_render_color(color);
        SDL_RenderFillRect(res.renderer, &dst);
    }
    // Something went wrong
    else
    {
        SDL_Log("Error in drawing GameObject");
        throw std::runtime_error("No drawable target");
    }
}

void GameObject::draw_mul(int mul)
{
    SDL_Rect dst = {int(px), int(py), mul*w, mul*h};

    // Draw the texture
    if(tex)
    {
        SDL_RenderCopyEx(res.renderer, tex, NULL, &dst, int(angle),
            NULL, SDL_FLIP_NONE);
        if(res.draw_hitbox)
        {
            res.set_render_color(res.get_color(COLOR_WHITE));
            SDL_RenderDrawRect(res.renderer, &dst);
        }
    }
    // Draw a rectangle
    else if(color)
    {
        res.set_render_color(color);
        SDL_RenderFillRect(res.renderer, &dst);
    }
    // Something went wrong
    else
    {
        SDL_Log("Error in drawing GameObject");
        throw std::runtime_error("No drawable target");
    }
}

void GameObject::update(float delta)
{
    // Do nothing by default
}

void GameObject::collide(GameObject& obj)
{
    // Do nothing by default
}

SDL_Rect GameObject::get_hitbox()
{
    return {int(px), int(py), w, h};
}

bool GameObject::remove()
{
    return finished;
}

void GameObject::set_active(bool set)
{
    active = set;
}

void GameObject::set_finished(bool set)
{
    finished = set;
}

void GameObject::set_texture(std::string name)
{
    this->tex = res.all_textures.at(name);
    SDL_QueryTexture(this->tex, NULL, NULL, &w, &h);
}

void GameObject::set_texture(SDL_Texture* tex)
{
    if(this->tex != tex) {
        this->tex = tex;
        SDL_QueryTexture(this->tex, NULL, NULL, &w, &h);
    }
}

bool GameObject::get_against()
{
    return against_player;
}

bool GameObject::get_active()
{
    return active;
}

bool GameObject::both_active(GameObject &obj)
{
    return (active && obj.get_active());
}

int GameObject::get_power()
{
    return power;
}

int GameObject::get_health()
{
    return health;
}
