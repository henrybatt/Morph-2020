#ifndef LINEDATA_H
#define LINEDATA_H

#include "Common.h"

typedef struct LineData{
    
    float angle = NO_LINE_ANGLE;
    float size = NO_LINE_SIZE;

    /* -- Constructors -- */
    LineData(){}
    LineData(float _angle, float _size) : angle(_angle), size(_size) {}

    bool onField(){return size == 0;}

} LineData;

#endif