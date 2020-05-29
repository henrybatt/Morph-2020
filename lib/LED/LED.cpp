#include <LED.h>

LED::LED(uint8_t _pin, unsigned long _duration) {
    pin = _pin;
    duration = _duration;
}

/* - Public - */

void LED::update(){
    if (millis() - lastUpdate > duration) {
        digitalWriteFast(pin, ledOn);
        ledOn = !ledOn;
        lastUpdate = millis();
    }
}