#ifndef LED_H
#define LED_H

#include <Common.h>

class LED{

    public:
        LED(uint8_t _pin, uint _duration);

        void update();

    private:

        bool ledOn = false;
        uint8_t pin;
        uint duration;
        uint lastUpdate;

};

#endif
