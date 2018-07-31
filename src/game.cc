#include "effects.hh"
#include "game.hh"
#include "object.hh"
#include "resources.hh"
#include "stone.hh"
#include <functional>
#include <iostream>
#include <string>
#include <typeinfo>

Game::Game(Resources &res)
:res(res), level(res, this), running(true), playing(true), paused(false),
 state(STATE_MENU)
{
    init();
}

Game::~Game()
{
    for(auto menu: menus)
        delete menu;
    for(auto label: labels)
        delete label;
    for(auto effect: layer_effects)
        delete effect;
}

void Game::init()
{
    // Create menus
    menus.push_back(new Menu(res, this)); // MENU_MAIN
    menus.push_back(new Menu(res, this)); // MENU_OPTIONS

    // Add content to main menu
    Label* logo = new Label(res, "spacesurf", res.font_l);
    logo->update_color_main(res.get_color(COLOR_BLUE));
    logo->update_pos(res.screen_w/2, 30);
    labels.push_back(logo);

    menus.at(MENU_MAIN)->add_item(new MenuLabel(
        res, "play", res.font_m,
        std::bind(&Game::start_level, this, STATE_GAME)));
    menus.at(MENU_MAIN)->add_item(new MenuLabel(
        res, "options", res.font_m,
        std::bind(&Game::change_menu, this, MENU_OPTIONS)));
    menus.at(MENU_MAIN)->add_item(new MenuLabel(
        res, "exit", res.font_m,
        std::bind(&Game::quit, this)));

    menus.at(MENU_OPTIONS)->add_item(new MenuLabel(
        res, "model", res.font_m,
        std::bind(&Game::quit, this)));
    menus.at(MENU_OPTIONS)->add_item(new MenuLabel(
        res, "difficulty", res.font_m,
        std::bind(&Game::quit, this)));
    menus.at(MENU_OPTIONS)->add_item(new MenuLabel(
        res, "back", res.font_m,
        std::bind(&Game::change_menu, this, MENU_MAIN)));

    // Set current menu to main menu
    current_menu = menus.at(MENU_MAIN);
    
    new_ray.restart();
}

void Game::input()
{
    if(state == STATE_MENU)
    {
        current_menu->input();
    }
    else if(state == STATE_GAME)
    {
        if(res.get_keyboard_key_d("P") ||
           res.get_controller_button_d(SDL_CONTROLLER_BUTTON_A))
        {
            pause();
        }
        else if(res.get_keyboard_key_d("I") ||
                res.get_controller_button_d(SDL_CONTROLLER_BUTTON_B))
        {
            play();
            level.init();
        }

        level.input();
    }
}

void Game::update(float delta_time)
{
    if(!paused)
    {
        add_rays();
        level.update_layer(delta_time, layer_effects);
    }

    if(state == STATE_MENU)
    {
        current_menu->update(delta_time);
    }
    else if(state == STATE_GAME)
    {
        if(!is_paused())
        {
            level.update(delta_time);
        }
    }
}

void Game::draw()
{
    // Cool pixel art n stuff
    SDL_SetRenderTarget(res.renderer, res.framebuffer);
    res.window_clear();
    
    // Always draw the effect layer
    level.draw_layer(layer_effects);

    if(state == STATE_MENU)
    {
        for(auto label: labels)
            label->draw_center();
        current_menu->draw();    
    }
    else if(state == STATE_GAME)
    {
        level.draw();
    }

    SDL_SetRenderTarget(res.renderer, NULL);
    SDL_RenderCopy(res.renderer, res.framebuffer, NULL, NULL);
}

void Game::add_rays()
{
    if(new_ray.time() > 0.08)
    {
        new_ray.restart();
        layer_effects.emplace_back(new Ray(res, *this));
    }
}

void Game::change_menu(unsigned menu)
{
    current_menu = menus.at(menu);
}

void Game::change_state(game_state state)
{
    this->state = state;
}

void Game::start_level(game_state state)
{
    this->state = state;
    //level.init();
}

void Game::quit()
{
    running = false;
}

void Game::play(bool p)
{
    playing = p;
}

void Game::pause()
{
    paused = !paused;
}

bool Game::is_running()
{
    return running;
}

bool Game::is_playing()
{
    return playing;
}

bool Game::is_paused()
{
    return paused;
}

Level* Game::get_level()
{
    return &level;
}
