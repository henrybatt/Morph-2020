#ifndef LINEDATA_H
#define LINEDATA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>


struct LineData{

    float angle;
    uint8_t state;

    LineData(){
        angle = NO_LINE_ANGLE;
        state = NO_LINE_STATE;
    }

    LineData(float angle, uint8_t state) : angle(angle), state(state) {}

    bool onField(){
        return state == 0;
    }


    /* -- Operators -- */
    bool operator == (LineData line2){
        return angle == line2.angle && state == line2.state;
    }

    bool operator != (LineData line2){
        return angle != line2.angle || state != line2.state;
    }

};


#endif