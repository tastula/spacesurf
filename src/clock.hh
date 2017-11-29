#ifndef SURF_CLOCK_HH
#define SURF_CLOCK_HH

class Clock
{
    public:
        Clock();
        ~Clock();
        void pause();
        float time();
        float restart();
    private:
        void init();

        bool paused;
        float start_time;
        float pause_time;
        float current_time;
};

#endif // SURF_CLOCK_HH
