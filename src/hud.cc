#include "hud.hh"
#include <iostream>

#define BAR_LENGTH(res) (res.screen_w/2)
#define HUD_BORDER 1

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
    x_now = x_left - 2*HUD_BORDER;
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
    if(x_now+w < x_right+2*HUD_BORDER || time_elapsed < time_max)
    {
        float distance = x_right - x_left - w + 2*HUD_BORDER;
        x_now = x_left + distance*(time_elapsed/time_max);    
    }
    else
    {
        x_now = x_right - w + 2*HUD_BORDER;
    }

    // Update labels
    health.update_text(std::to_string(hp));
    if(time_max > int(time_elapsed))
        time.update_text(std::to_string(int(time_elapsed)));
    else
        time.update_text(std::to_string(int(time_max)));
}

void HUD::draw()
{
    float y_top = 2 + 3;
    float y_btm = 2;

    // Background
    SDL_Rect r1 = {
        int(x_left-HUD_BORDER), int(y_top-HUD_BORDER),
        BAR_LENGTH(res)+2*HUD_BORDER, int(y_btm)+2*HUD_BORDER
    };
    res.set_render_color(res.get_color(COLOR_WHITE));
    SDL_RenderFillRect(res.renderer, &r1);

    // Line after head
    SDL_Rect r2 = {int(x_left), int(y_top), BAR_LENGTH(res), int(y_btm)};
    res.set_render_color(res.get_color(COLOR_GREY3));
    SDL_RenderFillRect(res.renderer, &r2);

    // Line before head
    SDL_Rect r3 = {int(x_left), int(y_top), int(x_now-x_left), int(y_btm)};
    res.set_render_color(res.get_color(res.current_naut));
    SDL_RenderFillRect(res.renderer, &r3);

    // The head itself
    SDL_Rect dts = {int(x_now), int(2), w, h};
    SDL_RenderCopy(res.renderer, tex, NULL, &dts);

    // Draw labels
    health.draw_right(x_left-4, 2);
    time.draw(x_right+4, 2);
}

void HUD::set_time(float time)
{
    time_elapsed = time;
}
