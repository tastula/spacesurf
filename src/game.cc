#include "effects.hh"
#include "game.hh"
#include "object.hh"
#include "resources.hh"
#include "stone.hh"

Game::Game(Resources &res)
:res(res), level(res, this), running(true), playing(true), paused(false)
{
    init();
}

Game::~Game()
{
}

void Game::init()
{
}

void Game::input()
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

void Game::update(float delta)
{
    if(!is_paused())
    {
        level.update(delta);
    }
}

void Game::draw()
{
    // Cool pixel art n stuff
    SDL_SetRenderTarget(res.renderer, res.framebuffer);
    res.window_clear();
    level.draw();
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

void Game::level_add_object(GameObject* obj)
{
    level.add_object(obj);
}
