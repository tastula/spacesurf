#ifndef SURF_MENU_HH
#define SURF_MENU_HH

#include "resources.hh"
#include <vector>

class Resources;
class Game;

class MenuItem;
class MenuLabel;
class MenuPair;

class Menu
{
    public:
        Menu(Resources &res, Game* game);
        ~Menu();
        void add_item(MenuItem* item);
        void input();
        void update(float delta);
        void draw();

    private:
        Resources& res;
        Game* game;
        unsigned index;

        std::vector<MenuItem*> items;
};

class MenuItem
{
    public:
        MenuItem();
        ~MenuItem();
        void draw();

    private:
        int x; int y;
        int w; int h;
};

class MenuLabel: public MenuItem
{
    public:
        MenuLabel();
        ~MenuLabel();
};

class MenuPair: public MenuItem
{
    public:
        MenuPair();
        ~MenuPair();
};

#endif
