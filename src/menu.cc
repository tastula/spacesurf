#include "menu.hh"
#include <iostream>

Menu::Menu(Resources& res)
: res(res), index(0)
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

void Menu::add_drawable(GameObject* item)
{
    drawables.push_back(item);
}

void Menu::input()
{
    if(res.get_keyboard_key_d("S") && index < items.size()-1) index++;
    if(res.get_keyboard_key_d("W") && index > 0) index--;

    items.at(index)->input();
}

void Menu::update(float delta)
{
    for(unsigned i = 0; i < items.size(); ++i){
        items.at(i)->update_pos(res.screen_w/2, res.screen_h/2
                                + ((int)i-index)*20);
        if(i == index)
            items.at(i)->get_label()->update_color_main(
                    res.get_naut_color()
            );
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

// --- ModelMenu ---------------------------------------------------------------

ModelMenu::ModelMenu(Resources& res)
: Menu(res), model(nullptr)
{
    model = new GameObject(res);
    model->set_position(res.screen_w-170, 0.4*res.screen_h);

    auto skills = res.get_naut_skills();
    int n_skills = 3;
    for(auto skill: skills) {
        std::string text = skill.first + ": " + std::to_string(skill.second);
        labels.push_back(new Label(
            res, text, res.font_s,
            res.screen_w-170, res.screen_h/2 + 10*n_skills
        ));
        n_skills++;
    }
}

ModelMenu::~ModelMenu()
{
    delete model;
}

void ModelMenu::update(float delta)
{
    model->set_texture(res.get_naut_texture());
    for(unsigned i = 0; i < items.size(); ++i){
        items.at(i)->update_pos(120, res.screen_h/2 + ((int)i-index)*20);
        if(i == index)
            items.at(i)->get_label()->update_color_main(res.get_naut_color());
        else 
            items.at(i)->get_label()->update_color_main(res.get_color(
                COLOR_WHITE
            ));
    }

    auto skills = res.get_naut_skills();
    int i = 0;
    for(auto skill: skills) {
        std::string text = skill.first + ": " + std::to_string(skill.second);
        labels[i]->update_text(text);
        i++;
    }

}

void ModelMenu::draw()
{
    model->draw_mul(3);
    for(auto item: items)
        item->draw_left();
    for(auto label: labels)
        label->draw();
}

// --- MenuItem ----------------------------------------------------------------

MenuItem::MenuItem(Resources& res)
: res(res)
{
}

MenuItem::MenuItem(Resources& res, std::string text, TTF_Font* font)
: res(res)
{
    label_name = new Label(res, text, font);
}

MenuItem::MenuItem(Resources& res, Label* label)
: res(res), label_name(label)
{
}

MenuItem::~MenuItem()
{
}

void MenuItem::input()
{
    // Nothing by default
}

void MenuItem::draw()
{
    label_name->draw_center();
}

void MenuItem::draw_left()
{
    label_name->draw(true);
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

MenuLabel::MenuLabel(Resources& res, std::string text, TTF_Font* font,
                     std::function<void()> callback)
: MenuItem(res, text, font), callback(callback)
{
}

MenuLabel::~MenuLabel()
{
    delete label_name;
}

void MenuLabel::input()
{
    if(res.get_keyboard_key_d("Space")) callback();
}

// --- MenuPair ----------------------------------------------------------------

/*
MenuPair::MenuPair()
{
}

MenuPair::~MenuPair()

{
}
*/
