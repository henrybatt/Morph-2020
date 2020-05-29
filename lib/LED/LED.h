#ifndef LED_H
#define LED_H

#include <Common.h>

class LED{

    public:

        /* -- Constructor (duration in milliseconds) -- */
        LED(uint8_t _pin, unsigned long _duration);

        /* -- Check timer and change state -- */
        void update();

    private:

        bool ledOn = false; // Led State
        uint8_t pin; // LED's Pin
        unsigned long duration;  // Time for cycle
        unsigned long lastUpdate;  // Time of last cycle
};

#endif
