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

bool CutScene::is_finished()
{
    return finished;
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
    player.set_active(false);
    player.set_position(-100, res.screen_h/2);
    rocks.stop();
    finished = false;
}

void StartCutScene::end()
{
    //std::cout << "Cutscene over" << std::endl;
    player.set_active(true);
    player.set_position(end_pos_x, res.screen_h/2);
    rocks.restart();
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


constexpr float ACCELERATION = 10;

WinCutScene::WinCutScene(Player& player, Clock& rocks, Resources& res)
: player(player),
  rocks(rocks),
  res(res),
  end_pos_x(res.screen_w * 5/4)
{
    init();
}

WinCutScene::~WinCutScene()
{
    // Pass
}

void WinCutScene::init()
{
    //std::cout << "Cutscene initialized" << std::endl;
    player.set_active(false);
    rocks.stop();
    finished = false;
}

void WinCutScene::end()
{
    //std::cout << "Cutscene over" << std::endl;
    finished = true;
}

void WinCutScene::update(float delta)
{
    if(!finished)
    {
        std::cout << wait.time() << std::endl;
        if(wait.time() > 1)
        {
            player.add_position(player.get_velocity()*delta*1.75, 0);
            //std::cout << "Cutscene updated" << std::endl;
        }
        else if(end_pos_x < player.get_px())
        {
            end();
        }
    }
}
