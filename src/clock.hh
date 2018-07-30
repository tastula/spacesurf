#ifndef SURF_CLOCK_HH
#define SURF_CLOCK_HH

class Clock
{
    public:
        Clock();
        ~Clock();
        void pause();
        void stop();
        float time();
        float restart();

        bool is_running();
    private:
        void init();

        bool paused;
        float start_time;
        float pause_time;
        float current_time;
};

#endif // SURF_CLOCK_HH
