#include "clock.hh"
#include <SDL2/SDL.h>

Clock::Clock()
{
    init();
}

Clock::~Clock()
{
}

void Clock::init()
{
    started = false;
    paused = false;
    start_time = 0;
    pause_time = 0;
    current_time = 0;
}

void Clock::start()
{
    started = true;
    start_time = SDL_GetTicks();
}

void Clock::pause()
{
    // Pause the clock
    if(started  and !paused)
    {
        paused = true;
        pause_time = SDL_GetTicks();
        current_time = pause_time-start_time;
    }
    // Restart counting
    else if(started and paused)
    {
        paused = false;
        start_time = SDL_GetTicks()-pause_time;
    }
}

void Clock::stop()
{
    started = false;
    current_time = SDL_GetTicks()-start_time;
}

float Clock::time()
{
    // Current time has to be defined if it's not saved
    if(started and !paused)
    {
        current_time = SDL_GetTicks()-start_time;
    }
    return current_time/1000;
}

float Clock::restart()
{
    float old_time = time();
    init();
    start();
    return old_time;
}
