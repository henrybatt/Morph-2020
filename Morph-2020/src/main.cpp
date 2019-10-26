#include <Arduino.h>
#include <Define.h>
#include <Common.h>


#include <Camera.h>


#include <BallData.h>
#include <LineData.h>
#include <Role.h>


#include <Bluetooth.h>

Camera Cam;
Bluetooth bt;

void setup() {


    Cam.init();

}

Role role = Role::undecided;

void loop() {
    // Cam.update();

    Serial.println(Cam.attack.visible());

    // bt.update(&role);

    // ballInfo.isOut = LightArray.isOutsideLine(heading, ballInfo.angle);
    // bluetoothData = BluetoothData(ballInfo, lineInfo, playMode, heading, position.robotPosition, Cam.defend.distance);
    // bt.update(&role, bluetoothData);




}


/* --  -- */