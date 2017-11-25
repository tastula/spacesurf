#include "effects.hh"
#include "game.hh"
#include "object.hh"
#include "resources.hh"

Game::Game(Resources &res)
:res(res), player(res, "naut1")
{
    init();
    player.set_position(200, 200);
    new_ray.start();
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
    update_rays();
    update_layers(delta);
    player.update(delta);
}

void Game::update_rays()
{
    if(new_ray.time() > 0.15)
    {
        new_ray.restart();
        res.layer1.emplace_back(new Ray(res));
    }
}

void Game::update_layers(float delta)
{
    for(unsigned i=0; i<res.layer1.size(); ++i)
    {
        res.layer1.at(i)->update(delta);
        if(res.layer1.at(i)->remove())
        {
            Object* del = res.layer1.at(i);
            res.layer1.erase(res.layer1.begin()+i);
            delete del;
            --i;
        }
    }
}

void Game::draw()
{
    draw_layers();
    player.draw();
}

void Game::draw_layers()
{
    for(unsigned i=0; i<res.layer1.size(); ++i)
    {
        res.layer1.at(i)->draw();
    }
}
