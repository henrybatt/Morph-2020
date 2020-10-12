#ifndef GOALDATA_H
#define GOALDATA_H

#include "Common.h"
// #include "Vector.h"

typedef struct GoalData{
    
    uint16_t angle = 65535;
    uint16_t distance = 0;

    /* -- Constructors -- */
    GoalData(){}
    GoalData(uint16_t _angle, uint16_t _distance) : angle(_angle), distance(_distance) {}

    bool visible(){return angle != 65535;}

    float calculateCentimeter(){return 123;}

} GoalData;

#endif