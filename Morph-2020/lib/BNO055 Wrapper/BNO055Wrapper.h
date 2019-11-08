#ifndef BNO055WRAPPER_H
#define BNO055WRAPPER_H

#include <Arduino.h>
#include <Common.h>

#include <Wire.h>
#include <bno055_driver.h>

#include <MPU.h>

class BNO055Wrapper{

    public:

        /* -- Class Constructor + Init -- */
        BNO055Wrapper();

        void update();

        void calibrate();

        float getHeading();

    private:

    struct bno055_t bno055 = {0};

    float heading = 0;

};

extern BNO055Wrapper bnoWrapper;

#endif