#ifndef SURF_GAMEOBJECT_HH
#define SURF_GAMEOBJECT_HH

#include "object.hh"
#include <SDL2/SDL.h>
#include <string>

class Game;
class Resources;

class GameObject : public Object
{
    public:
        GameObject(Resources &res, Game& game, std::string name);
        GameObject(Resources &res, Game& game);
        virtual ~GameObject();
        virtual void draw();
        virtual void update(float delta);
        virtual void collide(GameObject& obj);
        virtual SDL_Rect get_hitbox();
        virtual bool remove();

        void set_active(bool set);
        void set_texture(std::string tex);
        void set_texture(SDL_Texture *tex);
        bool get_against();
        bool get_active();
        bool both_active(GameObject& obj);
        int get_power();
        int get_health();

    protected:
        void init();

        Game& game;
        SDL_Texture *tex;
        SDL_Color* color;
        bool active;
        bool finished;
        bool collidable;
        bool against_player;
        float angle;
        float health;
        float power;
};

#endif // SURF_GAMEOBJECT_HH
