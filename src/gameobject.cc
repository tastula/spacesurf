#include "gameobject.hh"
#include "resources.hh"

GameObject::GameObject(Resources& res, Game& game, std::string name)
:Object(res), game(game)
{
    set_texture(name);
    GameObject::init();
}

GameObject::GameObject(Resources &res, Game &game)
:Object(res), game(game)
{
    // NB! Texture is not set, implement own draw()
    tex = nullptr;
    init();
}

GameObject::~GameObject()
{
    // Destructor
}

void GameObject::init()
{
    finished = false;
    collidable = true;
    against_player = false;
    angle = 0;
    health = 1;
    power = 0;
}

void GameObject::draw()
{
    SDL_Rect dts = {int(px), int(py), w, h};
    SDL_RenderCopyEx(res.renderer, tex, NULL, &dts, int(angle),
                     NULL, SDL_FLIP_NONE);
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
    // Never destroy by default
    return false;
}

void GameObject::set_texture(std::string name)
{
    this->tex = res.all_textures.at(name);
    SDL_QueryTexture(this->tex, NULL, NULL, &w, &h);
}

void GameObject::set_texture(SDL_Texture* tex)
{
    this->tex = tex;
    SDL_QueryTexture(this->tex, NULL, NULL, &w, &h);
}

bool GameObject::get_against()
{
    return against_player;
}

int GameObject::get_power()
{
    return power;
}

int GameObject::get_health()
{
    return health;
}
