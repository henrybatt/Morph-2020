#ifndef MPU_H
#define MPU_H

#include <Common.h>

#include <I2C.h>

class MPU{

    public:

        /* -- Class Constructor + Init -- */
        MPU();

        /* -- Read sensor + update heading -- */
        void update();

        /* -- Calibrate drift -- */
        void calibrate();

        /* -- Return MPU heading -- */
        float getHeading();



    private:

        float heading;

        /* -- Read from desired sensor -- */
        Vector3D readAccelerometer();
        Vector3D readGyroscope();
        Vector3D readMagnetometer();

        /* -- Convert raw values -- */
        float convertRawAcceleration(int16_t raw);
        float convertRawGyro(int16_t raw);

        long previousTime;
        long previousDrift;
        float calibration;
        float drift = 0;

};

extern MPU mpu;

#endif