#include "level.hh"
#include "resources.hh"
#include "stone.hh"

Level::Level(Resources& res)
:res(res), player(res, "naut1"), hud(res)
{
    init();
}

Level::~Level()
{
}

void Level::init()
{
    new_stone.restart();

    player.init();
    player.set_position(200, 200);
}

void Level::input()
{
    player.input();
}

void Level::update(float delta)
{
    // No need to update or draw player as it's done from Game
    add_stones();

    for(auto o1: res.layer2)
    {
        handle_collision(*o1, player); 
    }

    player.update(delta);
    hud.update(delta, player.get_health());
}

void Level::draw()
{
    // No need to update or draw player as it's done from Game
    player.draw();
    hud.draw();
}

void Level::add_stones()
{
    if(new_stone.time() > 0.3 && res.game_playing)
    {
        new_stone.restart();
        res.layer2.emplace_back(new Stone(res));
    }
}

void Level::handle_collision(Object& o1, Object& o2)
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
