#ifndef BLUETOOTHDATA_H
#define BLUETOOTHDATA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

#include <BallData.h>
#include <LineData.h>
#include <Role.h>
#include <Vector.h>

struct BluetoothData{

    BallData ballData;
    LineData lineData;
    Role role;
    Vector robotPosition;
    uint16_t heading;

    BluetoothData(){
        ballData = BallData();
        lineData = LineData();
        role = Role::undecided;
        robotPosition = Vector();
        heading = 0;
    }

    BluetoothData(BallData ballData, LineData lineData, Role role, Vector robotPosition, uint16_t heading) : 
                    ballData(ballData), lineData(lineData), role(role), robotPosition(robotPosition), heading(heading) {}

};


#endif
