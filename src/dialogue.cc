#include "dialogue.hh"
#include "resources.hh"
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL2/SDL.h>


Dialogue::Dialogue(Resources& res, std::string path)
:Object(res), text(res, "", res.font_s)
{
    // Load dialogue information from file
    std::ifstream stream(path);
    stream >> information;
    stream.close();

    border_outer = 10;
    border_inner = 2;
    dia_w = res.screen_w - 2*border_outer;
    dia_h = 40;
    dia_x = border_outer;
    dia_y = res.screen_h - border_outer - dia_h;
    back_w = res.screen_w - 2*border_outer + 2*border_inner;
    back_h = dia_h + 2*border_inner;
    back_x = border_outer - border_inner;
    back_y = res.screen_h - border_outer - border_inner - dia_h;
    text_w = ((res.screen_w-border_outer-border_inner) - (10+2+40)) / 8;

    lines = split_text(information["test"], text_w);

    for(unsigned i = 0; i < 3; ++i) {
        line_labels.push_back(Label(res, "", res.font_s));
    }
}


Dialogue::~Dialogue() {}


void Dialogue::draw()
{

    // A bit larger background box (borders)
    SDL_Rect back = { back_x, back_y, back_w, back_h };
    res.set_render_color(res.get_color(COLOR_GREY1));
    SDL_RenderFillRect(res.renderer, &back);

    // Actual dialogue box
    SDL_Rect front = { dia_x, dia_y, dia_w, dia_h };
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
    for(unsigned i = 0; i < line_labels.size(); ++i) {
        line_labels[i].update_text(lines[i]);
        line_labels[i].update_pos(x+40, y+5 + 10*i);
        line_labels[i].draw();
    }

}

std::vector<std::string> Dialogue::split_text(const std::string& text, int w) {

    std::vector<std::string> split_lines;

    // The whole line fits
    if(text.length() <= w) {
        split_lines.push_back(text);
        return split_lines;
    }

    std::string::const_iterator it_l = text.cbegin();
    std::string::const_iterator it_r = text.cbegin() + w;

    // Iterate the whole text to split lines
    while(it_l != text.cend()) {
        // Find a break point (space)
        if(it_r != text.cend() && *it_r != ' ') {
            --it_r;
        }
        // Save a substring as a separate line and continue
        else {
            // Save the first line as is
            if(it_l == text.cbegin()) {
                split_lines.push_back(std::string(it_l, it_r));
            }
            // Save the other lines without space in the beginning
            else {
                split_lines.push_back(std::string(it_l + 1, it_r));
            }
            it_l = it_r;
            it_r = it_l + w;
        }
    }

    //for(auto line: split_lines) std::cout << line << std::endl;

    return split_lines;
}
