#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <Common.h>

struct MoveData{
    int16_t angle = NO_ANGLE;
    int8_t speed = NO_SPEED;
    int8_t correction = NO_CORRECTION;

    /* -- Constructors -- */
    MoveData() {}

    MoveData(int16_t angle, int8_t speed) : angle(angle), speed(speed) {}

    MoveData(int16_t angle, int8_t speed, int8_t correction) : angle(angle), speed(speed), correction(correction) {}

    MoveData(const MoveData& movement, int8_t correction) : angle(movement.angle), speed(movement.speed), correction(correction) {}

};

#endif