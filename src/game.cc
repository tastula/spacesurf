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
    if(res.get_pressed_key() == "Space")
    {
        pause();
    }
    else if(res.get_pressed_key() == "I")
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
    level.draw();
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

void Game::level_add_stone(Stone *stone)
{
    level.add_stone(stone);
}
