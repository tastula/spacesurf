#include "dialogue.hh"
#include "resources.hh"
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>


Dialogue::Dialogue(Resources& res, std::string path)
:Object(res), text(res, "", res.font_s)
{
    // Load dialogue information from file
    std::ifstream stream(path);
    stream >> information;
    stream.close();

    // Test print
    std::cout << information["test"] << std::endl;
}


Dialogue::~Dialogue() {}


void Dialogue::draw()
{
    // A bit larger background box (borders)
    SDL_Rect back = {
        10-2, res.screen_h-10-40-2,
        res.screen_w-2*10+4, 40+4
    };
    res.set_render_color(res.get_color(COLOR_GREY1));
    SDL_RenderFillRect(res.renderer, &back);

    // Actual dialogue box
    SDL_Rect front = {
        10, res.screen_h-10-40,
        res.screen_w-2*10, 40
    };
    res.set_render_color(res.get_color(COLOR_GREY3));
    SDL_RenderFillRect(res.renderer, &front);

    // Talking head
    int w, h;
    int x = 10+2;
    int y = res.screen_h-50+2;
    SDL_Texture* head = res.get_naut_head();
    SDL_QueryTexture(head, NULL, NULL, &w, &h);
    SDL_Rect head_box = { x+5, y+5, w*3, h*3 };
    SDL_RenderCopy(res.renderer, head, NULL, &head_box);

    // The text
    text.update_text(information["test"]);
    text.update_pos(x+40, y+20);
    text.draw();

}
