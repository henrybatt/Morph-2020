#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

// Timer class. Check if a certain time has elapsed
class Timer {
public:
    /* -- Constructor - Millisec -- */
    Timer(unsigned long duration);
    void update();
    bool timeHasPassed();
    bool timeHasPassedNoUpdate();

    void resetTime();

private:
    unsigned long timerDuration;
    unsigned long lastUpdate;
};

class TimerM{
    public:
        /* -- Constructor - Microsec -- */
        TimerM(unsigned long duration);
        void update();
        bool timeHasPassed();
        bool timeHasPassedNoUpdate();

        void resetTime();

    private:
        unsigned long timerDuration;
        unsigned long lastUpdate;
};

#endif // TIMER_H
