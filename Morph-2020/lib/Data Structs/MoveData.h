#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

struct MoveData{
    uint16_t angle;
    uint8_t speed;
    uint8_t correction;

    MoveData() {}

    MoveData(double angle, double speed) : angle(angle), speed(speed) {}

    MoveData(double angle, double speed, double correction) : angle(angle), speed(speed), correction(correction) {}

};

#endif