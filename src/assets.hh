#ifndef SURF_ASSETS_HH
#define SURF_ASSETS_HH

#include "gameobject.hh"
#include <string>

class Resources;

class Surfboard: public GameObject
{
    public:
        Surfboard(Resources& res, Game& game, std::string name);
        virtual ~Surfboard();

        void update(float vy, float nx, float ny);
};

class Gun: public GameObject
{
    public:
        Gun(Resources& res, Game& game, std::string name);
        virtual ~Gun();

        virtual void update(float nx, float ny);

        void input();
    private:
        void shoot();
};

class Bullet: public GameObject
{
    public:
        Bullet(Resources& res, Game& game, int nx, int ny);
        virtual ~Bullet();

        virtual void collide(GameObject& obj);
        virtual void update(float delta);
};

#endif // SURF_ASSETS_HH
