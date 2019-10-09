#ifndef LINEDATA_H
#define LINEDATA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>


struct LineData{

    double angle;
    double size;
    bool onField;

    LineData(){
        angle = NO_LINE_ANGLE;
        size = NO_LINE_SIZE;
        onField = true;
    }

    LineData(double angle, double size) : angle(angle), size(size) {}

    LineData(double angle, double size, bool onField) : angle(angle), size(size), onField(onField) {}


    /* -- Operators -- */

    bool operator == (LineData line2){
        return angle == line2.angle && size == line2.size && onField == line2. onField;
    }

    bool operator != (LineData line2){
        return angle != line2.angle || size != line2.size || onField != line2.onField;
    }

};


#endif