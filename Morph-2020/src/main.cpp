#include <Arduino.h>
#include <Common.h>

#include <IMU.h>
#include <LSArray.h>
#include <TSSP.h>
#include <Camera.h>
#include <Bluetooth.h>
#include <RoleManager.h>
#include <MotorController.h>

#include <PID.h>
#include <Timer.h>

#include <MoveData.h>
#include <RoleData.h>
#include <Vector.h>

Timer BTSendTimer = Timer(BT_UPDATE_TIME);

float heading;

MoveData moveData;


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWriteFast(LED_BUILTIN, HIGH);

    imu.init();
    lightArray.init();
    tssps.init();
    camera.init();
    bluetooth.init();
    roleManager.init();
    motors.init();

    digitalWriteFast(LED_BUILTIN, LOW);

}


void loop() {

    imu.update();
    lightArray.update(heading);
    tssps.update();

    #if CAMERA
        camera.update();
    #endif

    if (BTSendTimer.timeHasPassed() && SWITCHING){
        bluetooth.update(BluetoothData(tssps.getBallData(), lightArray.getLineData(), roleManager.getRole(), heading, Vector()));
        roleManager.update();
    }

    motors.update(moveData);

    // roleManager.roleLED();

    """ Remove all ints and doubles """;


}


/* --  -- */