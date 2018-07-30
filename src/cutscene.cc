#include "cutscene.hh"
#include "clock.hh"
#include "player.hh"

CutScene::CutScene()
: finished(false)
{
    // Pass
}

CutScene::~CutScene()
{
    // Pass
}

StartCutScene::StartCutScene(Player* player, Clock* rocks,
                   float screen_w, float screen_h)
: player(player),
  rocks(rocks),
  end_pos_x(screen_w/6)
{
    init(screen_w, screen_h);
}

StartCutScene::~StartCutScene()
{
    // Pass
}

void StartCutScene::init(float screen_w, float screen_h)
{
    finished = false;
    player->set_position(screen_w-200, screen_h/2);
}

void StartCutScene::end()
{
    player->set_position(end_pos_x, 0);
    finished = true;
}

void StartCutScene::update(float delta)
{
    if(!finished)
    {
        if(player->get_px() < end_pos_x)
        {
            player->add_position(player->get_vx()*delta, 0);
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
