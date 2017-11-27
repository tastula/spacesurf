#include "hud.hh"

#define BAR_LENGTH 600

HUD::HUD(Resources& res, float time_max)
:res(res), health(res, "", res.font_m), time(res, "", res.font_m),
 time_max(time_max), time_elapsed(0)
{
    x_left = res.screen_w/2 - BAR_LENGTH/2;
    x_right = res.screen_w/2 + BAR_LENGTH/2;
    x_now = x_left;
    tex = res.all_textures.at("head1");
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
}

HUD::~HUD()
{
}

void HUD::update(float delta, int hp)
{
    // Update progress bar
    time_elapsed += delta; 
    if(x_now+w < x_right)
    {
        float distance = x_right - x_left - w;
        x_now = x_left + distance*(time_elapsed/time_max);    
    }
    else
    {
        x_now = x_right - 40;
    }

    // Update labels
    health.update_text(std::to_string(hp));
    time.update_text(std::to_string(int(time_elapsed)));
}

void HUD::draw()
{
    float y_top = 10 + 15;
    float y_btm = 10;

    // Line before head
    SDL_Rect r1 = {int(x_left), int(y_top), int(x_now-x_left), int(y_btm)};
    SDL_SetRenderDrawColor(res.renderer, 140, 10, 10, 255);
    SDL_RenderFillRect(res.renderer, &r1);

    // Line after head
    SDL_Rect r2 = {int(x_now), int(y_top), int(x_right-x_now), int(y_btm)};
    SDL_SetRenderDrawColor(res.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(res.renderer, &r2);

    // The head itself
    SDL_Rect dts = {int(x_now), int(10), w, h};
    SDL_RenderCopy(res.renderer, tex, NULL, &dts);


    // Draw labels
    health.draw_right(x_left-20, 15);
    time.draw(x_right+20, 15);
}
