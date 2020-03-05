#include <Common.h>

#include <TSSPArray.h>
#include <LightArray.h>

#include <Timer.h>


Timer updateTimer = Timer(TSSP_PERIOD_NUM * TSSP_PERIOD_TIME);

void send(){


    // Write both starting bytes
    SLAVE_SERIAL.write(SLAVE_START_BYTE);
    SLAVE_SERIAL.write(SLAVE_START_BYTE);

    // Write ball angle
    SLAVE_SERIAL.write(highByte((uint16_t)tssps.getAngle()));
    SLAVE_SERIAL.write(lowByte((uint16_t)tssps.getAngle()));

    // Write ball strength
    SLAVE_SERIAL.write(highByte((uint16_t)tssps.getStrength()));
    SLAVE_SERIAL.write(lowByte((uint16_t)tssps.getStrength()));

    // Write line angle
    SLAVE_SERIAL.write(highByte((uint16_t)lightArray.getAngle()));
    SLAVE_SERIAL.write(lowByte((uint16_t)lightArray.getAngle()));

    // Write line strength * 100 (remove decimal)
    SLAVE_SERIAL.write(highByte((uint16_t)lightArray.getSize() * 100));
    SLAVE_SERIAL.write(lowByte((uint16_t)lightArray.getSize() * 100));
}


void setup() { SLAVE_SERIAL.begin(TEENSY_BAUD); }


void loop() {

    tssps.read();

    if (updateTimer.timeHasPassedNoUpdate()) {

        tssps.update();
        lightArray.update();

        send();

    }

}

/* --  -- */

