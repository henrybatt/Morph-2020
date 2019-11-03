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

/*
float bounds(float lightAngle, float ballAngle){

    Serial.print(" , ");
    Serial.print(mod(mod(lightAngle + 180, 360) - ballAngle, 360));

  if((mod(lightAngle + 180 - ballAngle, 360)) > 0 && (mod(lightAngle + 180 - ballAngle, 360)) < 180){
    // need to move on upper bound
    return mod(lightAngle + 60, 360);
  }
  else{
    // lower bound
    return mod(lightAngle - 60, 360);
  }


}


void testing(){

    float orbitAngle = 160;
    float ballAngle = 160;

    float lineAngle = 315;
    float returnLineAngle = mod(lineAngle + 180, 360);

    float newMove = 0;

    if (smallestAngleBetween(returnLineAngle, ballAngle) < 90){

        if (smallestAngleBetween(returnLineAngle, orbitAngle) < 60){
            newMove = orbitAngle;
            Serial.print("Normal");
        } else if (smallestAngleBetween(returnLineAngle, orbitAngle) < 150){
            Serial.print("Bounds");
            newMove = bounds(returnLineAngle, orbitAngle);
        } else {
            Serial.print("STOP");
            newMove = -1;
        }

    } else {
        newMove = 420;
    }

    Serial.print(" , ");
    Serial.println(newMove);

}
*/

void loop() {

    imu.update();
    lightArray.update(imu.getHeading());
    tssps.update();

    #if CAMERA
        camera.update();
        coordManager.update();
    #endif

    if (BTSendTimer.timeHasPassed() && SWITCHING){
        bluetooth.update(BluetoothData(tssps.getBallData(), lightArray.getLineData(), roleManager.getRole(), imu.getHeading(), coordManager.getRobotPosition()));
        roleManager.update();
    }

    motors.update(directionManager.update());

    roleManager.roleLED();

    """ REDO VECTORS BAD!!!!!!!!!!! """;



    // testing();


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
