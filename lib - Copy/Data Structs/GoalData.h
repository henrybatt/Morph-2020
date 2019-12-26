#ifndef GOALDATA_H
#define GOALDATA_H

#include <Common.h>

class GoalData{

    public: 
        uint16_t angle;
        uint16_t distance;

        GoalData(){
            angle = 65535;
            distance = 65535;
        }

        GoalData(uint16_t angle, uint16_t distance) : angle(angle), distance(distance) {}

        /* -- Goal is visible -- */
        bool visible(){
            return angle != 65535;
        }

        /* -- Calculate distance towards goal in centimeters -- */
        float calculateCentimeter(){
            return 0.00000353067 * pow(MATH_E, 0.0288427 * (distance + 500)) - 25.0921;
        }


};


#endif