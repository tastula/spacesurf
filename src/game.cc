#include "game.hh"
#include "resources.hh"

Game::Game(Resources &res)
:res(res), player(res, "naut1")
{
    init();
    player.set_position(200, 200);
}

Game::~Game()
{
}

void Game::init()
{
}

void Game::input()
{
    player.input();
}

void Game::update(float delta)
{
    player.update(delta);
}

void Game::draw()
{
    player.draw();
}
