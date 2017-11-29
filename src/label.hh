#ifndef SURF_LABEL_HH
#define SURF_LABEL_HH

#include "object.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Resources;

class Label: public Object
{
    public:
        Label(Resources &res, std::string text, TTF_Font *font,
              float pos_x=0, float pos_y=0);
        virtual ~Label();
        virtual void draw();
        void draw_right();
        void draw_center();
        void draw(float new_x, float new_y);
        void draw_right(float new_x, float new_y);
        void draw_center(float new_x, float new_y);
        void update_text(std::string text);
        void update_pos(float new_x, float new_y);
        void update_font(TTF_Font *font);
        void update_color_main(SDL_Color* color);
        void update_color_back(SDL_Color* color);

    protected:
        void init();
        void update_texture();

        std::string text;
        TTF_Font *font;
        float pos_x;
        float pos_y;
        SDL_Texture* tex;
        float angle;
        int w;
        int h;
        SDL_Color* color_main;
        SDL_Color* color_back;

};

#endif
