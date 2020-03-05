#ifndef AVOIDANCE_H
#define AVOIDANCE_H

#include <Common.h>

#include <MoveData.h>
#include <LineData.h>


class Avoidance{

    public:

        /* -- Constructor -- */
        Avoidance();

        /* --  -- */
        MoveData update(MoveData calcMove, LineData lineData, uint16_t ballAngle, float heading);

        /* -- return if angle is inside the field -- */
        bool isOutsideLine(float angle, float heading);

    private:

        LineData avoidData = LineData();

};

extern Avoidance avoid;

#endif