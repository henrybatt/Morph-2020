#ifndef BLUETOOTHDATA_H
#define BLUETOOTHDATA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

#include <BallData.h>
#include <LineData.h>
#include <RoleData.h>
#include <Vector.h>

struct BluetoothData{

    BallData ballData;
    LineData lineData;
    Role role;
    uint16_t heading;
    Vector robotPosition;

    BluetoothData(){
        ballData = BallData();
        lineData = LineData();
        role = Role::undecided;
        heading = 0;
        robotPosition = Vector();
    }

    BluetoothData(BallData ballData, LineData lineData, Role role, uint16_t heading, Vector robotPosition) : 
                    ballData(ballData), lineData(lineData), role(role), heading(heading), robotPosition(robotPosition) {}

};


#endif
