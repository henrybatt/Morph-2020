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

#include <PID.h>
#include <Timer.h>

#include <MoveData.h>
#include <RoleData.h>
#include <Vector.h>

Timer BTSendTimer = Timer(BT_UPDATE_TIME);

void setup() {}

float heading;
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

    directionManager.update();

    motors.update(MoveData(270, 10, 0));

    roleManager.roleLED();


    """ Remove all ints and doubles """;


}


/* --  -- */