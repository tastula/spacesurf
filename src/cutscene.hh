#ifndef SURF_CUTSCENE_HH
#define SURF_CUTSCENE_HH

class Player;
class Clock;
class Resources;

//! A class that contains commands for executing a non-playable cutscene. Every
//! CutScene should be a unique object derived from the main class. Cutscenes
//! shouldn't be able to draw anything, just control and update other objects
//! that are given as pointers in the constructor.
class CutScene
{
    public:
        //! Base class constructor sets the state of cutscene as active.
        //! @brief Constructor for class CutScene.
        CutScene();

        //! Base class destructor shoudln't do anything.
        //! @brief Dummy destructor for class CutScene.
        virtual ~CutScene() = 0;

        //! Initializer where the state of objects in the cutscene is modified.
        //! Can be called to reset the cutscene.
        //! @brief Initialize the cutscene.
        virtual void init() = 0;

        //! End the current CutScene by setting critical variables to their end
        //! value. End conditions are checked in update().
        //! @brief End the current CutScene.
        virtual void end() = 0;

        //! Update the CutScene variables. Check if the CutScene is over by comparing
        //! critical variables to their end conditions.
        //! @brief Update the CutScene.
        //! @param Time passed since last call.
        virtual void update(float delta) = 0;

        //! If all critical variables have met the end conditions, the CutScene
        //! is marked as finished.
        //! @brief Check if the CutScene is over.
        virtual bool is_finished() = 0;

    protected:
        bool finished;
};

//! A class that creates a level starting CutScene. Player hovers from the left,
//! outside of the screen and starts the level at the same time as the rocks.
class StartCutScene : public CutScene
{
    public:
        //! Control player's movement and delay the rocks until the player is
        //! ready to start.
        //! @brief A CutScene that starts every level.
        //! @param Reference to player model.
        //! @param Reference to rock timer.
        //! @param Reference to game resources.
        StartCutScene(Player& player, Clock& rocks, Resources& res);

        virtual ~StartCutScene();

        void init() override;
        virtual void end() override;
        virtual void update(float delta) override;
        virtual bool is_finished() override;

    private:
        Player& player;
        Clock& rocks;
        Resources& res;
        const float end_pos_x;
};

#endif // SURF_CUTSCENE_HH