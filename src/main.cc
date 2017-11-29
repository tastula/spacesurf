#include "clock.hh"
#include "game.hh"
#include "resources.hh"
#include <SDL2/SDL.h>

int main()
{
    Resources res;
    Game game(res);

    Clock delta_timer;
    float delta_time = 0;

    // Run the game
    while(game.is_running())
    {
        delta_time = delta_timer.restart();

        // Check for user events
        while(SDL_PollEvent(&res.event))
        {
            if(res.event.type == SDL_QUIT ||
               res.get_keyboard_key_d("Escape") ||
               res.get_controller_button_d(SDL_CONTROLLER_BUTTON_Y))
            {
                return 0;
            }
            game.input();
        }

        // What's up with the game
        game.update(delta_time);
        game.draw();

        // Present all changes
        res.window_draw();
    }

    return 0;
}
