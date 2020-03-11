#include "dialogue.hh"
#include "game.hh"
#include "effects.hh"
#include "level.hh"
#include "levelinfo.hh"
#include "object.hh"
#include "resources.hh"
#include "stone.hh"
#include "cutscene.hh"
#include "dialogue.hh"
#include <iostream>

// Load level information from file
LevelInfo level = load_level("res/levels/tutorial.sl");

Level::Level(Resources& res, Game* g)
:res(res), game(*g), player(res, game), hud(res, level.length)
 //current_cutscene(nullptr),
 //current_dialogue(res, "res/dialogue/dia1.json")
 //current_dialogue(nullptr)
{
    init();
}

Level::~Level()
{
    //delete current_cutscene;
    //delete current_dialogue;
}

void Level::init()
{
    // Get rid of the old influences
    lose();

    game.play(true);

    player.init();
    player.set_texture(res.get_naut_texture());
    hud.init();

    //current_cutscene = new StartCutScene(res, this);
    
    //std::cout << "Level initialized" << std::endl;
}

void Level::input()
{
    player.input();
}

void Level::update(float delta)
{
    //if(hud.get_time() >= level.length && !current_cutscene) {
    //    current_cutscene = new WinCutScene(
    //        player, new_stone, res, game, layer2, player.get_health()
    //    );
    //}

    /**
    if(current_cutscene) {
        // Update ongoing cutscene
        if(current_cutscene->is_finished() == false)
        {
            current_cutscene->update(delta);
        }
        // The cutscene is over, delete it and continue the game normally
        else if(current_cutscene->is_finished())
        {
            delete current_cutscene;
            //delete current_dialogue;
            current_cutscene = nullptr;
            //current_dialogue = nullptr;
        }
    }
    **/

    //if(!current_cutscene) {
        add_stones();
        hud.update(delta, player.get_health());
    //}

    for(auto o1: layer2)
    {
        // Collide bad objects to good objects ONLY
        if(!o1->get_against()) continue;

        handle_collision(*o1, player);
        for(auto o2: layer2)
        {
            handle_collision(*o1, *o2);
        }
    }

    player.update(delta);
    if(!layer2.empty()) update_layer(delta, layer2);

    //std::cout << "Level updated" << std::endl;
}

void Level::draw()
{
    player.draw();
    draw_layer(layer2);
    hud.draw();

    //std::cout << current_dialogue << " " << (current_dialogue == nullptr) << std::endl;
    //if(current_dialogue != nullptr) current_dialogue->draw();

    //if(current_dialogue != nullptr) current_dialogue->draw();

    //std::cout << "Level drawn" << std::endl;
}

void Level::add_stones()
{
    if(new_stone.time()*1000 > level.spawn_min && game.is_playing())
    {
        new_stone.restart();
        layer2.emplace_back(new Stone(res, game));
    }
}

void Level::handle_collision(GameObject& o1, GameObject& o2)
{
    SDL_Rect r1 = o1.get_hitbox();
    SDL_Rect r2 = o2.get_hitbox();
    bool a1 = o1.get_against();
    bool a2 = o2.get_against();

    if(a1 != a2 && SDL_HasIntersection(&r1, &r2) && o1.both_active(o2))
    {
        o1.collide(o2);
        o2.collide(o1);
    }
}

void Level::lose()
{
    deactivate_objects();
}

void Level::deactivate_objects()
{
    for(auto obj: layer2)
    {
        obj->set_active(false);
    }
}

void Level::add_object(GameObject* obj)
{
    new_objects.push_back(obj);
}

void Level::update_layer(float delta, std::vector<GameObject*>& layer)
{
    // Update old objects first
    for(auto obj: layer)
    {
        obj->update(delta);
    }

    // Concatenate vectors
    if(&layer == &layer2)
    {
        layer.insert(layer.end(), new_objects.begin(), new_objects.end());
        new_objects.clear();
    }

    // Delete if needed
    for(unsigned i=0; i<layer.size(); ++i)
    {
        if(layer.at(i)->remove())
        {
            Object* del = layer.at(i);
            layer.erase(layer.begin()+i);
            delete del;
            --i;
        }
    }
}

void Level::draw_layer(std::vector<GameObject*>& layer)
{
    for(unsigned i=0; i<layer.size(); ++i)
    {
        layer.at(i)->draw();
    }
}
