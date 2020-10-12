#include <MPU.h>

MPU mpu = MPU();

/* - Public - */

MPU::MPU(){
    Wire.begin();
    I2CwriteByte(MPU9250_ADDRESS, 29, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 26, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_1000_DPS);
    I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_2_G);
    I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
    I2CwriteByte(MAG_ADDRESS, 0x0A, 0x16);
    previousTime = micros();
    calibrate();
}


void MPU::update(){
    float reading = readGyroscope().z;
    long currentTime = micros();

    heading +=  -(((float)(currentTime - previousTime) / 1000000.0) * (reading - calibration));
    if(millis() - previousDrift > 100) {
        heading += drift;
        previousDrift = millis();
    }
	heading = floatMod(heading, 360.0);

	previousTime = currentTime;

    #if DEBUG_COMPASS
        Serial.print(heading);
        Serial.print(", ");
        Serial.println(correction);
    #endif
}


void MPU::calibrate(){
    for (uint8_t i = 0; i < MPU_CALIBRATION_COUNT; i++) {
        float readingGyro = (float)readGyroscope().z;
        calibration += readingGyro;
        delay(MPU_CALIBRATION_TIME);
    }
    calibration /= MPU_CALIBRATION_COUNT;
    update();
    float firstVal = heading;
    delay(100);
    update();
    float secondVal = heading;
    drift = secondVal - firstVal;
    previousDrift = millis();
}


float MPU::getHeading(){
    return heading;
}

/* - Private - */

Vector3D MPU::readAccelerometer() {
    uint8_t buffer[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, buffer);

    int16_t ax = -(buffer[0] << 8 | buffer[1]);
    int16_t ay = -(buffer[2] << 8 | buffer[5]);
    int16_t az = buffer[4] << 8 | buffer[5];

    Vector3D returnVector = {convertRawAcceleration(ax), convertRawAcceleration(ay), convertRawAcceleration(az)};
    return returnVector;
}


Vector3D MPU::readGyroscope() {
    uint8_t buffer[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, buffer);

    int16_t gx = -(buffer[8] << 8 | buffer[1]);
    int16_t gy = -(buffer[10] << 8 | buffer[11]);
    int16_t gz = buffer[12] << 8 | buffer[13];

    Vector3D returnVector = {convertRawGyro(gx), convertRawGyro(gy), convertRawGyro(gz)};
    return returnVector;
}


Vector3D MPU::readMagnetometer() {
    uint8_t status1;
    do {
        I2Cread(MAG_ADDRESS, 0x02, 1, &status1);
    } while (!(status1 & 0x01));

    uint8_t mag[7];
    I2Cread(MAG_ADDRESS, 0x03, 7, mag);

    int16_t mx = -(mag[3] << 8 | mag[2]);
    int16_t my = -(mag[1] << 8 | mag[0]);
    int16_t mz = -(mag[5] << 8 | mag[4]);

    Vector3D returnVector = {(float)mx, (float)my, (float)mz};
    return returnVector;
}

float MPU::convertRawAcceleration(int16_t raw) {
    float a = (raw * 2.0) / 32768.0;
    return a;
}


float MPU::convertRawGyro(int16_t raw) {
    float g = (raw * 1000.0) / 32768.0;
    return g;
}