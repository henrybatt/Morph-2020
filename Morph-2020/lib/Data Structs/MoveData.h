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

    MoveData(uint16_t angle, uint8_t speed) : angle(angle), speed(speed) {}

    MoveData(uint16_t angle, uint8_t speed, uint8_t correction) : angle(angle), speed(speed), correction(correction) {}

};

#endif