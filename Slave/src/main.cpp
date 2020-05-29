#include <Common.h>

#include <TSSPArray.h>
#include <LightArray.h>

#include <Timer.h>
#include <LED.h>


TimerM updateTimer = TimerM(TSSP_PERIOD_NUM * TSSP_PERIOD_TIME);
LED slaveLED = LED(LED_BUILTIN, SLAVE_LED_DURATION);

void send(){

    // Write starting bytes
    MASTER_SERIAL.write(SLAVE_START_BYTE);
    MASTER_SERIAL.write(SLAVE_START_BYTE);

    // Write ball angle
    MASTER_SERIAL.write(highByte((uint16_t)tssps.getAngle()));
    MASTER_SERIAL.write(lowByte((uint16_t)tssps.getAngle()));

    // Write ball strength
    MASTER_SERIAL.write(highByte((uint16_t)tssps.getStrength()));
    MASTER_SERIAL.write(lowByte((uint16_t)tssps.getStrength()));

    // Write line angle
    MASTER_SERIAL.write(highByte((uint16_t)lightArray.getAngle()));
    MASTER_SERIAL.write(lowByte((uint16_t)lightArray.getAngle()));

    // Write line strength * 100 (remove decimal)
    MASTER_SERIAL.write(highByte((uint16_t)lightArray.getSize() * 100));
    MASTER_SERIAL.write(lowByte((uint16_t)lightArray.getSize() * 100));
}


void setup() { MASTER_SERIAL.begin(TEENSY_BAUD); }


void loop() {

    tssps.read();

    if (updateTimer.timeHasPassedNoUpdate()) {

        tssps.update();
        lightArray.update();

        send();

    }

    slaveLED.update();

}




/* --  -- */

