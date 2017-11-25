#include "effects.hh"
#include "game.hh"
#include "object.hh"
#include "resources.hh"

Game::Game(Resources &res)
:res(res), level(res)
{
    init();
}

Game::~Game()
{
}

void Game::init()
{
    new_ray.start();
}

void Game::input()
{
    if(res.get_pressed_key() == "Space")
    {
        res.game_paused = !res.game_paused;
    }
    
    level.input();
}

void Game::update(float delta)
{
    if(!res.game_paused)
    {
        add_rays();
        level.update(delta);
        update_layer(delta, res.layer1);
        update_layer(delta, res.layer2);
    }
}

void Game::add_rays()
{
    if(new_ray.time() > 0.08)
    {
        new_ray.restart();
        res.layer1.emplace_back(new Ray(res));
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
    draw_layer(res.layer2);
}

void Game::draw_layer(std::vector<Object*>& layer)
{
    for(unsigned i=0; i<layer.size(); ++i)
    {
        layer.at(i)->draw();
    }
}
