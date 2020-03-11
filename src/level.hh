#ifndef SURF_LEVEL_HH
#define SURF_LEVEL_HH

#include "clock.hh"
#include "dialogue.hh"
#include "hud.hh"
#include "player.hh"
#include <vector>

class Game;
class Dialogue;
class GameObject;
class Resources;
class Stone;
class Cutscene;

class Level
{
    friend class Game;
    friend class Cutscene;

    public:
        Level(Resources& res, Game* g);
        ~Level();
        void init();
        void input();
        void update(float delta);
        void draw();
        void handle_collision(GameObject& o1, GameObject& o2);
        void lose();

        // TODO: A ton of congigurations ad tweaking, this is the place
        // TODO: Read levels from a file, clocks with callbacks?

        void add_object(GameObject* obj);

    private:
        friend class CutScene;

        void deactivate_objects();
        void add_stones();
        void draw_layer(std::vector<GameObject*>& layer);
        void update_layer(float delta, std::vector<GameObject*>& layer);

        std::vector<GameObject*> layer2;
        std::vector<GameObject*> new_objects;

        bool scene_playing;
        bool game_playing;

        Resources& res;
        Game& game;
        Player player;
        Clock new_stone;
        HUD hud;
};

#endif
