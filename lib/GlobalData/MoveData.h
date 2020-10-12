#ifndef MOVEDATA_H
#define MOVEDATA_H

#include "Common.h"

typedef struct MoveData{

    float angle = NO_ANGLE;
    float speed = NO_SPEED;
    float correction = NO_CORRECTION;

    /* -- Constructors -- */
    MoveData() {}
    MoveData(float angle, float speed) : angle(angle), speed(speed) {}
    MoveData(float angle, float speed, float correction) : angle(angle), speed(speed), correction(correction) {}

} MoveData;





#endif