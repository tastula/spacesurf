#include "effects.hh"
#include "game.hh"
#include "object.hh"
#include "resources.hh"
#include "stone.hh"

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
    menus.at(MENU_MAIN)->add_drawable(new MenuLabel(res, logo));
    menus.at(MENU_MAIN)->add_item(new MenuLabel(res, "play", res.font_m));
    menus.at(MENU_MAIN)->add_item(new MenuLabel(res, "options", res.font_m));

    // Set current menu to main menu
    current_menu = menus.at(MENU_MAIN);
}

void Game::input()
{
    if(state == STATE_MENU)
    {
    
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

void Game::update(float delta)
{
    if(state == STATE_MENU)
    {
        current_menu->update(); 
    }
    else if(state == STATE_GAME)
    {
        if(!is_paused())
        {
            level.update(delta);
        }
    }
}

void Game::draw()
{
    // Cool pixel art n stuff
    SDL_SetRenderTarget(res.renderer, res.framebuffer);
    res.window_clear();
    
    if(state == STATE_MENU)
    {
        current_menu->draw();    
    }
    else if(state == STATE_GAME)
    {
        level.draw();
    }

    SDL_SetRenderTarget(res.renderer, NULL);
    SDL_RenderCopy(res.renderer, res.framebuffer, NULL, NULL);
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
