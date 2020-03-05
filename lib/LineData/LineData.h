#ifndef LINEDATA_H
#define LINEDATA_H

#include <Common.h>

struct LineData{

    float angle = NO_LINE_ANGLE;
    float size = NO_LINE_SIZE;

    /* -- Constructor -- */
    LineData() {}
    LineData(float angle, float size) : angle(angle), size(size) {}

    /* -- Robot is on field -- */
    bool onField(){ return size == 0; }

    /* -- Operators -- */
    bool operator == (LineData line2){
        return angle == line2.angle && size == line2.size;
    }

    bool operator != (LineData line2){
        return angle != line2.angle || size != line2.size;
    }

};


#endif
