#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

struct MoveData{
    int16_t angle;
    int8_t speed;
    int8_t correction;

    MoveData() {}

    MoveData(int16_t angle, int8_t speed) : angle(angle), speed(speed) {}

    MoveData(int16_t angle, int8_t speed, int8_t correction) : angle(angle), speed(speed), correction(correction) {}

};

#endif