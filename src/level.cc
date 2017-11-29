#include "game.hh"
#include "effects.hh"
#include "level.hh"
#include "object.hh"
#include "resources.hh"
#include "stone.hh"

Level::Level(Resources& res, Game* g)
:res(res), game(*g), player(res, game, "naut1"), hud(res, 100)
{
    init();
}

Level::~Level()
{
}

void Level::init()
{
    new_ray.restart();
    new_stone.restart();
    hud.set_time(0);
    player.init();
    player.set_position(200, 200);
    // Update other gear, too
    player.update(0);
}

void Level::input()
{
    player.input();
}

void Level::update(float delta)
{
    add_rays();
    add_stones();

    if(!layer1.empty()) update_layer(delta, layer1);

    for(auto o1: layer2)
    {
        // Collide bad objects to good objects ONLY
        if(!o1->get_against()) continue;

        handle_collision(*o1, player);
        for(auto o2: layer2)
        {
            handle_collision(*o1, *o2);
        }
    }

    player.update(delta);
    if(!layer2.empty()) update_layer(delta, layer2);
    hud.update(delta, player.get_health());
}

void Level::draw()
{
    draw_layer(layer1);
    player.draw();
    draw_layer(layer2);
    hud.draw();
}

void Level::add_stones()
{
    if(new_stone.time() > 0.3 && game.is_playing())
    {
        new_stone.restart();
        layer2.emplace_back(new Stone(res, game));
    }
}

void Level::add_rays()
{
    if(new_ray.time() > 0.08)
    {
        new_ray.restart();
        layer1.emplace_back(new Ray(res, game));
    }
}

void Level::handle_collision(GameObject& o1, GameObject& o2)
{
    SDL_Rect r1 = o1.get_hitbox();
    SDL_Rect r2 = o2.get_hitbox();
    bool a1 = o1.get_against();
    bool a2 = o2.get_against();

    if(a1 != a2 && SDL_HasIntersection(&r1, &r2))
    {
        o1.collide(o2);
        o2.collide(o1);
    }
}

void Level::add_object(GameObject* obj)
{
    new_objects.push_back(obj);
}

void Level::update_layer(float delta, std::vector<GameObject*>& layer)
{
    // Update old objects first
    for(auto obj: layer)
    {
        obj->update(delta);
    }

    // Concatenate vectors
    if(&layer == &layer2)
    {
        layer.insert(layer.end(), new_objects.begin(), new_objects.end());
        new_objects.clear();
    }

    // Delete if needed
    for(unsigned i=0; i<layer.size(); ++i)
    {
        if(layer.at(i)->remove())
        {
            Object* del = layer.at(i);
            layer.erase(layer.begin()+i);
            delete del;
            --i;
        }
    }
}

void Level::draw_layer(std::vector<GameObject*>& layer)
{
    for(unsigned i=0; i<layer.size(); ++i)
    {
        layer.at(i)->draw();
    }
}
