#ifndef BALLDATA_H
#define BALLDATA_H

#include "Common.h"

typedef struct BallData{

    uint16_t angle = TSSP_NO_BALL_ANGLE;
    uint16_t strength = TSSP_NO_BALL_STRENGTH;

    /* -- Constructor -- */
    BallData(){}
    BallData(uint16_t _angle, uint8_t _strength) : angle(_angle), strength(_strength) {}

    bool visible(){return strength != TSSP_NO_BALL_STRENGTH;}


} BallData;

#endif

