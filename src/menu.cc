#include "menu.hh"

Menu::Menu(Resources& res, Game* game)
: res(res), game(game), index(0)
{
}

Menu::~Menu()
{
    for(auto drawable: drawables)
        delete drawable;
    for(auto item: items)
        delete item;
}

void Menu::add_item(MenuItem* item)
{
    items.push_back(item);
}

void Menu::add_drawable(MenuItem* item)
{
    drawables.push_back(item);
}

void Menu::input()
{
    if(res.get_keyboard_key_d("D") && index < items.size()-1) index++;
    if(res.get_keyboard_key_d("W") && index > 0) index--;
}

void Menu::update(float delta)
{
    for(int i = 0; i < items.size(); ++i){
        items.at(i)->update_pos(res.screen_w/2, res.screen_h/2 + (i-index)*20);
        if(i == index)
            items.at(i)->get_label()->update_color_main(
                    res.get_color(COLOR_NAUT1
            ));
        else 
            items.at(i)->get_label()->update_color_main(
                    res.get_color(COLOR_WHITE
            ));
    }
}

void Menu::draw()
{
    for(auto item: items)
        item->draw();
    for(auto drawable: drawables)
        drawable->draw();
}

// --- MenuItem ----------------------------------------------------------------

MenuItem::MenuItem()
{
}

MenuItem::MenuItem(Resources& res, std::string text, TTF_Font* font)
{
    label_name = new Label(res, text, font);
}

MenuItem::~MenuItem()
{
}

void MenuItem::draw()
{
    label_name->draw_center();
}

void MenuItem::draw(int x, int y)
{
    label_name->draw(x, y);
}

void MenuItem::update_pos(int x, int y)
{
    label_name->update_pos(x, y);
}

Label* MenuItem::get_label()
{
    return label_name;
}

// --- MenuLabel ---------------------------------------------------------------

MenuLabel::MenuLabel(Resources& res, std::string text, TTF_Font* font)
: MenuItem(res, text, font)
{
}

MenuLabel::MenuLabel(Resources& res, Label* label)
{
    label_name = label;
}

MenuLabel::~MenuLabel()
{
    delete label_name;
}

// --- MenuPair ----------------------------------------------------------------

MenuPair::MenuPair()
{
}

MenuPair::~MenuPair()

{
}
