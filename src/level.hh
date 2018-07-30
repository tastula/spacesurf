#ifndef SURF_LEVEL_HH
#define SURF_LEVEL_HH

#include "clock.hh"
#include "hud.hh"
#include "player.hh"
#include <vector>

class Game;
class GameObject;
class Resources;
class Stone;
class CutScene;

class Level
{
    friend class Game;

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
        void deactivate_objects();
        void add_stones();
        void draw_layer(std::vector<GameObject*>& layer);
        void update_layer(float delta, std::vector<GameObject*>& layer);

        std::vector<GameObject*> layer2;
        std::vector<GameObject*> new_objects;

        // If a scene is playing. Player can't take input during one.
        bool is_scene;

        Resources& res;
        Game& game;
        Player player;
        Clock new_stone;
        HUD hud;
        CutScene* current_cutscene;
};

#endif
