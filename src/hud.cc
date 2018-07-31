#include "hud.hh"
#include <iostream>

#define BAR_LENGTH(res) (res.screen_w/2)

HUD::HUD(Resources& res, float time_max)
:res(res), health(res, "", res.font_s),
 time(res, "", res.font_s),
 time_max(time_max), time_elapsed(0)
{
    init();
}

HUD::~HUD()
{
}

void HUD::init()
{
    x_left = res.screen_w/2 - BAR_LENGTH(res)/2;
    x_right = res.screen_w/2 + BAR_LENGTH(res)/2;
    x_now = x_left;
    tex = res.all_textures.at("head1");
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    set_time(0);

    health.update_text("");
    time.update_text("");
}

void HUD::update(float delta, int hp)
{
    // Update progress bar
    time_elapsed += delta; 
    if(x_now+w < x_right || time_elapsed < time_max)
    {
        float distance = x_right - x_left - w;
        x_now = x_left + distance*(time_elapsed/time_max);    
    }
    else
    {
        x_now = x_right - 8;
    }

    // Update labels
    health.update_text(std::to_string(hp));
    time.update_text(std::to_string(int(time_elapsed)));
}

void HUD::draw()
{
    float y_top = 2 + 3;
    float y_btm = 2;

    // Line after head
    SDL_Rect r2 = {int(x_left), int(y_top), BAR_LENGTH(res), int(y_btm)};
    res.set_render_color(res.get_color(COLOR_WHITE));
    SDL_RenderFillRect(res.renderer, &r2);

    // Line before head
    SDL_Rect r1 = {int(x_left), int(y_top), int(x_now-x_left), int(y_btm)};
    res.set_render_color(res.get_color(res.current_naut));
    SDL_RenderFillRect(res.renderer, &r1);

    // The head itself
    SDL_Rect dts = {int(x_now), int(2), w, h};
    SDL_RenderCopy(res.renderer, tex, NULL, &dts);


    // Draw labels
    health.draw_right(x_left-4, 3);
    time.draw(x_right+4, 3);
}

void HUD::set_time(float time)
{
    time_elapsed = time;
}
