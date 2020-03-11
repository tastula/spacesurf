#ifndef SURF_CUTSCENE_HH
#define SURF_CUTSCENE_HH

#include "clock.hh"
#include "dialogue.hh"
#include <vector>

class Player;
class Resources;
class Game;
class GameObject;
class Level;

class Cutscene
{

    public:
        Cutscene(Resources& res, Level& level);

        virtual ~Cutscene();

        virtual void init();

        virtual void end();

        virtual void input();

        virtual void update(float delta);

        virtual void draw();

        virtual bool is_finished();

    protected:
        Resources& res;
        Level& level;
        bool finished;
        Clock clock;
        Dialogue* dialogue;
        unsigned action = 0;

        bool action_move_player(float delta, float px, float py);
        bool action_wait(float time);
        bool action_confirm_dialogue();
};



/**
//! A class that creates a level starting Cutscene. Player hovers from the left,
//! outside of the screen and starts the level at the same time as the rocks.
class StartCutscene : public Cutscene
{
    friend class Level;

    public:
        //! Control player's movement and delay the rocks until the player is
        //! ready to start.
        //! @brief A Cutscene that starts every level.
        //! @param Reference to player model.
        //! @param Reference to rock timer.
        //! @param Reference to game resources.
        StartCutscene(Player& player, Clock& rocks, Resources& res, Level& level);

        virtual ~StartCutscene();

        void init() override;
        virtual void end() override;
        virtual void update(float delta) override;

    private:
        Player& player;
        Clock& rocks;
        Resources& res;
        const float end_pos_x;
};


class WinCutscene : public Cutscene
{
    public:
        WinCutscene(Level& level, Player& player, Clock& rocks, Resources& res, Game& game,
                    std::vector<GameObject*>& layer, int hp);

        virtual ~WinCutscene();

        void init() override;
        virtual void end() override;
        virtual void update(float delta) override;

    private:
        Player& player;
        Clock& rocks;
        Clock wait;
        Resources& res;
        Game& game;
        std::vector<GameObject*>& layer;
        const float end_pos_x;
        Clock confetti;
        unsigned confetti_left = 10;
        const unsigned confetti_burst = 12;
};
**/

#endif // SURF_CUTSCENE_HH
