#include "Timer.h"


/* -- Millisecond Timer Class -- */

Timer::Timer(unsigned long duration) {
    timerDuration = duration;
}

void Timer::update() {
    lastUpdate = millis();
}

bool Timer::timeHasPassed() {
    if (millis() - lastUpdate > timerDuration) {
        update();
        return true;
    }

    return false;
}

bool Timer::timeHasPassedNoUpdate() {
    return millis() - lastUpdate > timerDuration;
}

void Timer::resetTime() {
    lastUpdate = millis();
}



/* -- Microsecond Timer Class -- */
TimerM::TimerM(unsigned long duration) {
    timerDuration = duration;
}

void TimerM::update() {
    lastUpdate = micros();
}

bool TimerM::timeHasPassed() {
    if (micros() - lastUpdate > timerDuration) {
        update();
        return true;
    }

    return false;
}

bool TimerM::timeHasPassedNoUpdate() {
    return micros() - lastUpdate > timerDuration;
}

void TimerM::resetTime() {
    lastUpdate = micros();
}