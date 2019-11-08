#include <Arduino.h>
#include <Common.h>

#include <BNO055Wrapper.h>
#include <LSArray.h>
#include <TSSP.h>
#include <Camera.h>
#include <CoordinateManager.h>
#include <Bluetooth.h>
#include <RoleManager.h>
#include <DirectionManager.h>
#include <MotorController.h>

#include <MoveData.h>
#include <Timer.h>

Timer BTSendTimer = Timer(BT_UPDATE_TIME);

void setup() {}


void loop() {
    
    // Update data
    bnoWrapper.update();
    lightArray.update(bnoWrapper.getHeading());
    tssps.update();

    #if CAMERA
        // Read camera data & calculate coordinates
        camera.update();
        coordManager.update(bnoWrapper.getHeading());
    #endif

    if (BTSendTimer.timeHasPassed() && SWITCHING){
        // Send bluetooth data and decide new role
        bluetooth.update(BluetoothData(tssps.getBallData(), lightArray.getLineData(), roleManager.getRole(), bnoWrapper.getHeading(), coordManager.getRobotPosition()));
        roleManager.update();
    }

    if (true){ // If touchscreen button enabled
        motors.update(directionManager.update(tssps.getBallData(), bnoWrapper.getHeading()));
    } else {
        motors.update(MoveData(0, 0, 0));
    }

    roleManager.roleLED();

}

/* --  -- */



/*

void orbit(){

    float angle;
    float strength

    float strengthModifier = (((float)strength - (float)BALL_FAR_STRENGTH) / ((float)BALL_CLOSE_STRENGTH - (float)BALL_FAR_STRENGTH));
    float value = angle > 180 ? angle - 360 : angle;
    float angleAddition = angleIsInside(325, 35, angle) ? (value * 1.1 * strengthModifier) : findSign(value) * (90 * strengthModifier);

    float moveAngle = angle + angleAddition;

    

}
*/
