#ifndef SURF_MENU_HH
#define SURF_MENU_HH

#include "label.hh"
#include "resources.hh"
#include <functional>
#include <vector>
#include <SDL2/SDL_ttf.h>

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
        void add_drawable(MenuItem* item);
        void input();
        void update(float delta);
        void draw();

    private:
        Resources& res;
        Game* game;
        unsigned index;

        std::vector<MenuItem*> items;
        std::vector<MenuItem*> drawables;
};

class MenuItem
{
    public:
        MenuItem(Resources& res);
        MenuItem(Resources& res, std::string text, TTF_Font* font);
        virtual ~MenuItem();
        virtual void input();
        virtual void draw();
        virtual void draw(int x, int y);
        virtual void update_pos(int x, int y);
        virtual Label* get_label();

    // TODO: inherit from Object
    protected:
        Resources& res;
        Label* label_name;
        int x; int y;
        int w; int h;
};

class MenuLabel: public MenuItem
{
    public:
        MenuLabel(Resources& res, std::string text, TTF_Font* font,
                  std::function<void()> callback);
        virtual ~MenuLabel();
        virtual void input();
    private:
        std::function<void()> callback;
};

/*
class MenuPair: public MenuItem
{
    public:
        MenuPair();
        ~MenuPair();
};
*/

#endif
