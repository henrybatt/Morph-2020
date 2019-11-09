#include <BNO055Wrapper.h>


BNO055Wrapper bnoWrapper = BNO055Wrapper();


BNO055Wrapper::BNO055Wrapper(){
    delay(100);
    Wire.begin();

    // setup BNO055 driver
    bno055.bus_read = bno055_read;
    bno055.bus_write = bno055_write;
    bno055.delay_msec = bno055_delay_ms;
    bno055.dev_addr = BNO055_I2C_ADDR2;

    s8 result = bno055_init(&bno055);
    result += bno055_set_power_mode(BNO055_POWER_MODE_NORMAL);

    result += bno055_set_operation_mode(BNO055_OPERATION_MODE_IMUPLUS); // Pg 22 of datasheet, section 3.3.1; NDOF or NDOF_FMC_OFF snap to magnetic north; IMUPLUS (acc + gyro fusion) if there is magnetic interference, otherwise M4G (basically relative mag)
    result == 0 ? Serial.println("BNO055 initialised") : Serial.printf("BNO055 init error: %d\n", result);
}


void BNO055Wrapper::update(){

    #if MPU_OVERRIDE
        mpu.update();
        heading = mpu.getHeading();
    #else 
        bno055_convert_float_euler_h_deg(&heading);
    #endif

    #if DEBUG_IMU
        Serial.printf("IMU:\tHeading: %i \n", heading);
    #endif


}


void BNO055Wrapper::calibrate(){

}


float BNO055Wrapper::getHeading(){
    return heading;
}