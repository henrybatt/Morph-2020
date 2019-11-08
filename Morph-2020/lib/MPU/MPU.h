#ifndef MPU_H
#define MPU_H

#include <Arduino.h>
#include <Common.h>

#include <I2C.h>

class MPU {

    public:

        /* -- Class Constructor + Init -- */
        MPU();

        /* -- Update MPU values -- */
        void update();

        /* -- Return heading -- */
        float getHeading();

    private:

        /* -- Calibrate MPU drift -- */
        void calibrate();

        /* -- read sensors of MPU -- */
        Vector3D readAccelerometer();
        Vector3D readGyroscope();
        Vector3D readMagnetometer();

        /* -- Convert raw data -- */
        float convertRawAcceleration(int raw);
        float convertRawGyro(int raw);

        float heading; // Compass heading

        long previousTime;
        long previousDrift;
        float calibration;
        float drift = 0;

};

extern MPU mpu;

#endif