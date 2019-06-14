#ifndef SURF_MENU_HH
#define SURF_MENU_HH

#include "label.hh"
#include "resources.hh"
#include "gameobject.hh"
#include <functional>
#include <vector>
#include <SDL2/SDL_ttf.h>

class Resources;
class GameObject;
class Game;
class Label;

class MenuItem;
class MenuLabel;
class MenuPair;

class Menu
{
    public:
        Menu(Resources &res);
        virtual ~Menu();
        void add_item(MenuItem* item);
        void add_drawable(GameObject* item);
        virtual void input();
        virtual void update(float delta);
        virtual void draw();

    protected:
        Resources& res;
        unsigned index;

        std::vector<MenuItem*> items;
        std::vector<GameObject*> drawables;
};

class ModelMenu: public Menu
{
    public:
        ModelMenu(Resources& res);
        virtual ~ModelMenu();
        virtual void update(float delta);
        virtual void draw();

    private:
        GameObject* model;
        std::vector<Label*> labels;
};

class MenuItem
{
    public:
        MenuItem(Resources& res);
        MenuItem(Resources& res, Label* label);
        MenuItem(Resources& res, std::string text, TTF_Font* font);
        virtual ~MenuItem();
        virtual void input();
        virtual void draw();
        virtual void draw_left();
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
