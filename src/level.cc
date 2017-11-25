#include "level.hh"
#include "resources.hh"
#include "stone.hh"

Level::Level(Resources& res)
:res(res)
{
    init();
}

Level::~Level()
{
}

void Level::init()
{
    new_stone.start();

    // Make sure player is first object in layer2
    player = new Player(res, "naut1");
    res.layer2.emplace_back(player);
    player->set_position(200, 200);
}

void Level::input()
{
    player->input();
}

void Level::update(float delta)
{
    // No need to update or draw player as it's done from Game
    add_stones();
}

void Level::draw()
{
    // No need to update or draw player as it's done from Game
}

void Level::add_stones()
{
    if(new_stone.time() > 0.3)
    {
        new_stone.restart();
        res.layer2.emplace_back(new Stone(res));
    }
}
