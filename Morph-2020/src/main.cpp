#include <Arduino.h>
#include <Common.h>

#include <IMU.h>
#include <LSArray.h>
#include <TSSP.h>
#include <Camera.h>
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
    #endif

    if (BTSendTimer.timeHasPassed() && SWITCHING){
        bluetooth.update(BluetoothData(tssps.getBallData(), lightArray.getLineData(), roleManager.getRole(), imu.getHeading(), Vector()));
        roleManager.update();
    }

    motors.update(directionManager.update());

    roleManager.roleLED();


    """ Remove all ints and doubles """;
    """ REDO VECTORS BAD!!!!!!!!!!! """;


}

/* --  -- */



/*
BallData ballInfo;

void orbit(){

    double angle;

    double strengthModifier = (((double)ballInfo.strength - (double)BALL_FAR_STRENGTH) / ((double)BALL_CLOSE_STRENGTH - (double)BALL_FAR_STRENGTH));
    double value = ballInfo.angle > 180 ? ballInfo.angle - 360 : ballInfo.angle;
    double angleAddition = angleIsInside(325, 35, angle) ? (value * 1.1 * strengthModifier) : findSign(value) * (90 * strengthModifier);

    double moveAngle = angle + angleAddition;

    

}
*/
