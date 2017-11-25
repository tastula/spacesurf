#ifndef SURF_CLOCK_HH
#define SURF_CLOCK_HH

class Clock
{
    public:
        Clock();
        ~Clock();
        void init();
        void start();
        void pause();
        void stop();
        float time();
        float restart();
    private:
        bool started;
        bool paused;
        float start_time;
        float pause_time;
        float current_time;
};

#endif
