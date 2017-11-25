#include "game.hh"
#include "resources.hh"

Game::Game(Resources &res)
:res(res), test(res, "yo mate", res.font_m, 100, 100)
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
}

void Game::update(float delta)
{
}

void Game::draw()
{
    test.draw();
}
