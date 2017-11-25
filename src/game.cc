#include "effects.hh"
#include "game.hh"
#include "object.hh"
#include "resources.hh"
#include "stone.hh"

Game::Game(Resources &res)
:res(res), player(res, "naut1")
{
    init();
    player.set_position(200, 200);
    new_ray.start();
    new_stone.start();
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
    add_rays();
    add_stones();
    update_layer(delta, res.layer1);
    player.update(delta);
    update_layer(delta, res.layer2);
}

void Game::add_rays()
{
    if(new_ray.time() > 0.08)
    {
        new_ray.restart();
        res.layer1.emplace_back(new Ray(res));
    }
}

void Game::add_stones()
{
    if(new_stone.time() > 0.3)
    {
        new_stone.restart();
        res.layer2.emplace_back(new Stone(res));
    }
}

void Game::update_layer(float delta, std::vector<Object*>& layer)
{
    for(unsigned i=0; i<layer.size(); ++i)
    {
        layer.at(i)->update(delta);
        if(layer.at(i)->remove())
        {
            Object* del = layer.at(i);
            layer.erase(layer.begin()+i);
            delete del;
            --i;
        }
    }
}

void Game::draw()
{
    draw_layer(res.layer1);
    player.draw();
    draw_layer(res.layer2);
}

void Game::draw_layer(std::vector<Object*>& layer)
{
    for(unsigned i=0; i<layer.size(); ++i)
    {
        layer.at(i)->draw();
    }
}
