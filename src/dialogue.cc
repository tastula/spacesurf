#include "dialogue.hh"
#include "resources.hh"
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL2/SDL.h>


Dialogue::Dialogue(Resources& res, std::string path)
:Object(res), ongoing(0), head(nullptr)
{
    // Load dialogue information from file
    std::ifstream stream(path);
    stream >> info;
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
    text_w = (dia_w - 36) / 8;

    load_dialogue();

    for(unsigned i = 0; i < 3; ++i) {
        line_labels.push_back(Label(res, "", res.font_s));
    }

    all_displayed = false;
    indicator.restart();
    display_indicator = false;
}


Dialogue::~Dialogue() {
    head = nullptr;
}

void Dialogue::load_dialogue() {
    lines = split_text(info["dialogue"][ongoing]["text"], text_w);
    head = res.get_dialogue_head(info["dialogue"][ongoing]["head"]);
    ongoing++;
}

void Dialogue::input()
{
    // Advance dialogue if there's lines to show
    if(res.get_keyboard_key_d("Space")) {
        if(lines.size() > 3) lines.erase(lines.begin(), lines.begin()+3);
        else {
            if(ongoing < info["dialogue"].size()) {
                load_dialogue();

            }
            else all_displayed = true;
        }
    }
}

void Dialogue::update(float delta)
{
    // Update indicator dot visibility to make it flash
    if(indicator.time() > 0.5) {
        display_indicator = !display_indicator;
        indicator.restart();
    }
}

void Dialogue::draw()
{
    //if(!is_showing) return;

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
    SDL_QueryTexture(head, NULL, NULL, &w, &h);
    SDL_Rect head_box = { dia_x+6, dia_y+6, w*3, h*3 };
    SDL_RenderCopy(res.renderer, head, NULL, &head_box);

    // Update text
    for(unsigned i = 0; i < line_labels.size(); ++i)
    {
        if(i < lines.size()) {
            line_labels[i].update_text(lines[i]);
            line_labels[i].update_pos(dia_x+2*6+w*3, dia_y+6 + 10*i);
            line_labels[i].draw();
        }
    }

    // If there's more to display, signal it with a dot
    if((lines.size() > 3 || info["dialogue"].size() > ongoing) && display_indicator)
    {
        SDL_Rect rect = {
            res.screen_w-border_outer-border_inner-10,
            res.screen_h-border_outer-border_inner-10,
            6, 6
        };
        res.set_render_color(res.get_color(COLOR_WHITE));
        SDL_RenderFillRect(res.renderer, &rect);
    }

}

bool Dialogue::is_read() {
    return all_displayed;
}

std::vector<std::string> Dialogue::split_text(const std::string& text, unsigned w) {

    std::vector<std::string> split_lines;

    // The whole line fits
    if(text.length() <= w) {
        split_lines.push_back(text);
        return split_lines;
    }

    std::string::const_iterator it_l = text.cbegin();
    std::string::const_iterator it_r = text.cbegin() + w;

    // Iterate the whole text
    while(it_l < text.cend()) {
        // Find a break point (space)
        if(it_r < text.cend() && *it_r != ' ') {
            --it_r;
        }
        // Save substrings as a separate line
        else {
            // Cut space out from lines that come after the first
            int space = it_l == text.cbegin() ? 0 : 1;
            // The line is shorter
            if(it_r >= text.cend()) {
                split_lines.push_back(std::string(it_l+space, text.cend()));
            }
            // The line fits or is too long
            else {
                split_lines.push_back(std::string(it_l+space, it_r));
            }
            it_l = it_r;
            it_r = it_l + w;
        }
    }

    for(auto line: split_lines) std::cout << line << std::endl;

    return split_lines;
}
