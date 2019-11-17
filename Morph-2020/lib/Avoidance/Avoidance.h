#ifndef AVOIDANCE_H
#define AVOIDANCE_H

#include <Arduino.h>
#include <Common.h>

#include <LineData.h>
#include <MoveData.h>
#include <BallData.h>

class Avoidance{

    public:
        Avoidance();

        void update(LineData lightData, BallData _ballData, float _heading);

        LineData getLineData();

        /* -- Calculate how to return from line -- */
        MoveData calculateAvoidance(MoveData calcMove);

        /* --  -- */
        bool isOutsideLine(float angle);

    private:

            /* -- Calculate Avoidance Bounce -- */
        MoveData calculateAvoianceBounce(MoveData calcMove, float returnAngle, float lineSize);

        /* -- Avoidance bounce angle -- */
        float calculateAvoianceBounceAngle(float orbitAngle, float lineAngle);

        BallData ballData; // Ball Information

        LineData lineData; // Line Data - absolute line vales

        float heading;


};

extern Avoidance avoid;

#endif
