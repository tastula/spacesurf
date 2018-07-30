#include "resources.hh"
#include "cutscene.hh"
#include "clock.hh"
#include "player.hh"
#include <iostream>

CutScene::CutScene()
: finished(false)
{
    // Pass
}

CutScene::~CutScene()
{
    // Pass
}

StartCutScene::StartCutScene(Player& player, Clock& rocks, Resources& res)
: player(player),
  rocks(rocks),
  res(res),
  end_pos_x(res.screen_w/4)
{
    init();
}

StartCutScene::~StartCutScene()
{
    // Pass
}

void StartCutScene::init()
{
    //std::cout << "Cutscene initialized" << std::endl;
    finished = false;
    player.set_active(false);
    player.set_position(-100, res.screen_h/2);
}

void StartCutScene::end()
{
    //std::cout << "Cutscene over" << std::endl;
    player.set_active(true);
    player.set_position(end_pos_x, res.screen_h/2);
    finished = true;
}

void StartCutScene::update(float delta)
{
    if(!finished)
    {
        if(player.get_px() < end_pos_x)
        {
            player.add_position(player.get_velocity()*delta*0.75, 0);
            //std::cout << "Cutscene updated" << std::endl;
        }
        else
        {
            end();
        }
    }
}

bool StartCutScene::is_finished()
{
    return finished;
}
