#include "menu.hh"

Menu::Menu(Resources& res, Game* game)
: res(res), game(game), index(0)
{
}

Menu::~Menu()
{
    for(auto item: items)
        delete item;
}

void Menu::add_item(MenuItem* item)
{
    items.push_back(item);
}

void Menu::input()
{
    if(res.get_keyboard_key_d("D") && index < items.size()-1) index++;
    if(res.get_keyboard_key_d("W") && index > 0) index--;
}

void Menu::update(float delta)
{
}

void Menu::draw()
{
    for(auto item: items)
        item->draw();
}

// --- MenuItem ----------------------------------------------------------------

MenuItem::MenuItem()
{
}

MenuItem::~MenuItem()
{
}

void MenuItem::draw()
{
}

// --- MenuLabel ---------------------------------------------------------------

MenuLabel::MenuLabel()
{
}

MenuLabel::~MenuLabel()
{
}

// --- MenuPair ----------------------------------------------------------------

MenuPair::MenuPair()
{
}

MenuPair::~MenuPair()

{
}
