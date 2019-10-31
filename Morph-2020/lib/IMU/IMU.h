#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Common.h>

#include <I2C.h>

class IMU {

    public:

        /* -- Class Constructor + Init -- */
        IMU();

        void update();

        float getHeading();

    private:

        void calibrate();

        Vector3D readAccelerometer();
        Vector3D readGyroscope();
        Vector3D readMagnetometer();

        float convertRawAcceleration(int raw);
        float convertRawGyro(int raw);

        float heading;

        long previousTime;
        long previousDrift;
        float calibration;
        float drift = 0;

};

extern IMU imu;

#endif