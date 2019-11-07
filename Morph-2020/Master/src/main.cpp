#include <Arduino.h>
#include <Common.h>

#include <IMU.h>
#include <LSArray.h>
#include <TSSP.h>
#include <Camera.h>
#include <CoordinateManager.h>
#include <Bluetooth.h>
#include <RoleManager.h>
#include <DirectionManager.h>
#include <MotorController.h>

#include <Timer.h>

Timer BTSendTimer = Timer(BT_UPDATE_TIME);

void setup() {}


void loop() {

    imu.update();
    lightArray.update(imu.getHeading());
    tssps.update();

    #if CAMERA
        camera.update();
        coordManager.update(imu.getHeading());
    #endif

    if (BTSendTimer.timeHasPassed() && SWITCHING){
        bluetooth.update(BluetoothData(tssps.getBallData(), lightArray.getLineData(), roleManager.getRole(), imu.getHeading(), coordManager.getRobotPosition()));
        roleManager.update();
    }

    motors.update(directionManager.update(tssps.getBallData(), imu.getHeading()));

    roleManager.roleLED();

}

/* --  -- */



/*
BallData ballInfo;

void orbit(){

    float angle;

    float strengthModifier = (((float)ballInfo.strength - (float)BALL_FAR_STRENGTH) / ((float)BALL_CLOSE_STRENGTH - (float)BALL_FAR_STRENGTH));
    float value = ballInfo.angle > 180 ? ballInfo.angle - 360 : ballInfo.angle;
    float angleAddition = angleIsInside(325, 35, angle) ? (value * 1.1 * strengthModifier) : findSign(value) * (90 * strengthModifier);

    float moveAngle = angle + angleAddition;

    

}
*/
