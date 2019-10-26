#include <Arduino.h>
#include <Define.h>
#include <Common.h>


#include <Camera.h>


#include <BallData.h>
#include <LineData.h>
#include <Role.h>


#include <Bluetooth.h>
#include <MotorController.h>


Camera Cam;
Bluetooth bt;

MotorController Motor;

void setup() {



    Motor.init();

    // Cam.init();
}

Role role = Role::undecided;

void loop() {
    // Cam.update();
    // bt.update(&role);


    """ REDO BLUETOOTH TO HAVE ROLE MANAGER """;

    // ballInfo.isOut = LightArray.isOutsideLine(heading, ballInfo.angle);
    // bluetoothData = BluetoothData(ballInfo, lineInfo, playMode, heading, position.robotPosition, Cam.defend.distance);
    // bt.update(&role, bluetoothData);

    Motor.update(MoveData(100,100,100));



}


/* --  -- */