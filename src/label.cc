#include "label.hh"
#include "resources.hh"

Label::Label(Resources &res, std::string text, TTF_Font *font,
             float pos_x, float pos_y)
:Object(res), text(text), font(font), pos_x(pos_x), pos_y(pos_y)
{
    init();
    update_texture();
}

Label::~Label()
{
    SDL_DestroyTexture(tex);
}

void Label::init()
{
    angle = 0;
    color_main = res.get_color(COLOR_WHITE);
    color_back = res.get_color(COLOR_WHITE);
}

void Label::draw()
{
    draw(pos_x, pos_y);
}

void Label::draw_right()
{
    draw(pos_x-w, pos_y);
}

void Label::draw_center()
{
    draw(pos_x-w/2, pos_y-h/2);
}

void Label::draw(float new_x, float new_y)
{
    SDL_Rect dst = {int(new_x), int(new_y), w, h};
    SDL_RenderCopyEx(res.renderer, tex, NULL, &dst, int(angle), NULL,
                     SDL_FLIP_NONE);
}

void Label::draw_right(float new_x, float new_y)
{
    draw(new_x-w, new_y);
}

void Label::draw_center(float new_x, float new_y)
{
    draw(new_x-w/2, new_y-h/2);
}

void Label::update_text(std::string text)
{
    if(this->text != text)
    {
        this->text = text;
        update_texture();
    }
}

void Label::update_pos(float new_x, float new_y)
{
    if(pos_x != new_x or pos_y != new_y)
    {
        pos_x = new_x;
        pos_y = new_y;
    }
}

void Label::update_font(TTF_Font *font)
{
    if(this->font != font)
    {
        this->font = font;
        update_texture();
    }
}

void Label::update_color_main(SDL_Color* color)
{
    if(color_main->r != color->r or color_main->g != color->g or
       color_main->b != color->b or color_main->a != color->a)
    {
        color_main = color;
        update_texture();
    }
}

void Label::update_color_back(SDL_Color* color)
{
    if(color_back->r != color->r or color_back->g != color->g or
       color_back->b != color->b or color_back->a != color->a)
    {
        color_back = color;
    }
}

void Label::update_texture()
{
    SDL_Surface *sur = TTF_RenderText_Solid(font, text.c_str(), *color_main);
    tex = SDL_CreateTextureFromSurface(res.renderer, sur);
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    SDL_FreeSurface(sur);
}
