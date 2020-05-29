#ifndef AVOIDANCE_H
#define AVOIDANCE_H

#include <Common.h>

#include <MoveData.h>
#include <LineData.h>
#include <BallData.h>


class Avoidance{

    public:

        /* -- Constructor -- */
        Avoidance();

        void data(BallData _ballData, LineData _lineData);

        /* --  -- */
        MoveData update(MoveData calcMove, float heading);

        /* -- return if angle is inside the field -- */
        bool isOutsideLine(float angle, float heading);

    private:

        LineData lineData = LineData();
        BallData ballData = BallData();

        LineData avoidData = LineData();

};

extern Avoidance avoid;

#endif