#include "clock.hh"
#include <SDL2/SDL.h>

Clock::Clock()
{
    init();
}

Clock::~Clock()
{
    // Destructor
}

void Clock::init()
{
    paused = false;
    start_time = 0;
    pause_time = 0;
    current_time = 0;
}

void Clock::pause()
{
    // Try to stop the clock if it's running
    stop();

    // Continue counting
    if(paused)
    {
        paused = false;
        start_time = SDL_GetTicks()-pause_time;
    }
}

float Clock::time()
{
    // Current time has to be defined if it's not saved
    if(!paused)
    {
        current_time = SDL_GetTicks()-start_time;
    }
    return current_time/1000;
}

float Clock::restart()
{
    float old_time = time();
    init();
    start_time = SDL_GetTicks();
    return old_time;
}

void Clock::stop()
{
    if(!paused)
    {
        paused = true;
        pause_time = SDL_GetTicks();
        current_time = pause_time-start_time;
    }
}

void Clock::reset() {
    current_time = 0;
}

bool Clock::is_running()
{
    return !paused;
}
