#include "resources.hh"
#include "cutscene.hh"
#include "clock.hh"
#include "player.hh"
#include "gameobject.hh"
#include "helpers.hh"
#include "effects.hh"
#include "level.hh"
#include <iostream>

Cutscene::Cutscene(Resources& res, Level& level)
: res(res), level(level), finished(false), dialogue(nullptr)
{
    level.scene_playing = true;
}

Cutscene::~Cutscene()
{
    // Pass
}

void Cutscene::init() {}

void Cutscene::end() {}

void Cutscene::input()
{
    if(dialogue) dialogue->input();
}

void Cutscene::update(float delta)
{
    if(dialogue) dialogue->update(delta);

    if(level.scene_playing) {
        if(action == 0 && action_move_player(delta, 100, res.screen_h/2)) {
            clock.restart();
            action++;
        }
        else if(action == 1 && action_wait(1)) {
            dialogue = new Dialogue(res, "res/dialogue/dia1.json");
            action++;
        }
        else if(action == 2 && action_confirm_dialogue()) {
            delete dialogue; dialogue = nullptr;
            clock.restart();
            action++;
        }
        else if(action == 3 && action_wait(0.5)) {
            level.scene_playing = false;
        }
    }
}

void Cutscene::draw() {
    if(dialogue) dialogue->draw();
}

bool Cutscene::is_finished()
{
    return finished;
}

bool Cutscene::action_move_player(float delta, float px, float py) {
    // Calculate direction to move towards
    int dx1 = px-level.player.get_px(); if(dx1 != 0) dx1 = dx1/abs(dx1);
    int dy1 = py-level.player.get_py(); if(dy1 != 0) dy1 = dy1/abs(dy1);

    // Move the player
    level.player.add_position(
        dx1*delta*level.player.get_velocity(),
        dy1*delta*level.player.get_velocity()
    );

    // Calculate current direction
    int dx2 = px-level.player.get_px(); if(dx2 != 0) dx2 = dx2/abs(dx2);
    int dy2 = py-level.player.get_py(); if(dy2 != 0) dy2 = dy2/abs(dy2);

    // Set the player to target point if moved past it
    if(dx1 != dx2) level.player.set_position(px, level.player.get_py());
    if(dy1 != dy2) level.player.set_position(level.player.get_px(), py);

    // Action completed if the player is on target point
    return px == level.player.get_px() && py == level.player.get_py();

}

bool Cutscene::action_wait(float time) {
    // Action completed when wanted time has passed
    return clock.time() > time;
}

bool Cutscene::action_confirm_dialogue() {
    // Action completed when all dialogue is read
    return dialogue->is_read();
}


/**
StartCutscene::StartCutscene(Player& player, Clock& rocks, Resources& res, Level& level)
: Cutscene(level), player(player),
  rocks(rocks),
  res(res),
  end_pos_x(res.screen_w/4)
{
    init();
}

StartCutscene::~StartCutscene()
{
    // Pass
}

void StartCutscene::init()
{
    //std::cout << "Cutscene initialized" << std::endl;
    player.set_active(false);
    player.set_position(-100, res.screen_h/2);
    rocks.stop();
    finished = false;
}

void StartCutscene::end()
{
    //std::cout << "Cutscene over" << std::endl;
    player.set_active(true);
    player.set_position(end_pos_x, res.screen_h/2);
    rocks.restart();
    finished = true;
}

void StartCutscene::update(float delta)
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

WinCutscene::WinCutscene(Level& level, Player& player, Clock& rocks, Resources& res,
                         Game& game, std::vector<GameObject*>& layer, int hp)
: Cutscene(level),
  player(player),
  rocks(rocks),
  res(res),
  game(game),
  layer(layer),
  end_pos_x(res.screen_w * 5/4),
  confetti_left(hp%10)
{
    init();
}

WinCutscene::~WinCutscene()
{
    // Pass
}

void WinCutscene::init()
{
    //std::cout << "Cutscene initialized" << std::endl;
    player.set_active(false);
    rocks.stop();
    finished = false;
}

void WinCutscene::end()
{
    //std::cout << "Cutscene over" << std::endl;
    finished = true;
}

void WinCutscene::update(float delta)
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
                        res, 2,conf_px, conf_py, conf_vx, conf_vy, 100,
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
**/