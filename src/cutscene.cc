#include "resources.hh"
#include "cutscene.hh"
#include "clock.hh"
#include "player.hh"
#include "gameobject.hh"
#include "helpers.hh"
#include "effects.hh"
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

WinCutScene::WinCutScene(Player& player, Clock& rocks, Resources& res,
                         Game& game, std::vector<GameObject*>& layer, int hp)
: player(player),
  rocks(rocks),
  res(res),
  game(game),
  layer(layer),
  end_pos_x(res.screen_w * 5/4),
  confetti_left(hp%10)
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
        if(wait.time() > 1)
        {
            player.add_position(player.get_velocity()*delta*1.75, 0);
            //std::cout << "Cutscene updated" << std::endl;
            if(confetti_left != 0 && confetti.time() > 0.5)
            {
                const float conf_px = random_interval(
                    res.screen_w*5/6, res.screen_w
                );
                const float conf_py = random_interval(0, res.screen_h);

                const int offset = 25;
                const unsigned possible_colors[5] = {
                    COLOR_CONFETTI1, COLOR_CONFETTI2, COLOR_CONFETTI3,
                    COLOR_CONFETTI4, COLOR_CONFETTI5
                };

                for(unsigned i = 0; i < confetti_burst; i++)
                {
                    const float conf_vx = random_interval(-offset, offset);
                    const float conf_vy = random_interval(-offset, offset);
                    const int color = random_interval(0, 100);

                    Particle* conf = new Particle(
                        res, game, 2,conf_px, conf_py, conf_vx, conf_vy, 100,
                        possible_colors[color%5]
                    );
                    layer.emplace_back(conf);
                }

                confetti_left -= 1;
                confetti.restart();
            }

        }
        else if(end_pos_x < player.get_px() && wait.time() > 5)
        {
            end();
        }
    }
}
