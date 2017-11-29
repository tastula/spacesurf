#ifndef SURF_GAME_HH
#define SURF_GAME_HH

#include "clock.hh"
#include "level.hh"
#include "player.hh"
#include <vector>

class Resources;
class Stone;

class Game
{
    public:
        Game(Resources &res);
        Game(const Game& other) = delete;
        ~Game();
        void init();
        void input();
        void update(float delta);
        void draw();
        
        void quit();
        void play(bool p = true);
        void pause();

        bool is_running();
        bool is_playing();
        bool is_paused();

        // Workarounds to allow accessing Level from GameObjects
        // Maybe passing Level reference or making it public would help?
        void level_add_object(GameObject* obj);

    private:
        void add_rays();

        Resources& res;
        Level level;

        bool running;
        bool playing;
        bool paused;
};

#endif
