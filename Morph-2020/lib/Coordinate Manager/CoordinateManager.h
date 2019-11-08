#ifndef COORDINATEMANAGER_H
#define COORDINATEMANAGER_H

#include <Arduino.h>
#include <Common.h>

#include <TSSP.h>
#include <Camera.h>

#include <MoveData.h>
#include <Vector.h>
#include <PID.h>
#include <Timer.h>

class CoordinateManager{

    public:

        /* -- Class Constructor -- */
        CoordinateManager();

        /* -- Update coordinates -- */
        void update(float _heading);

        /* -- Move to coordinate - two types - -- */
        bool moveToCoord(MoveData *calcMove, Vector target); // Return if at coordinate
        MoveData moveToCoord(Vector target); // Return movement data

        /* -- Return position vectors -- */
        Vector getRobotPosition();
        Vector getBallPosition();

        /* -- If the coordinates have been recalculated recently -- */
        bool newCoordUpdate();

        /* -- Vectors of data -- */
        Vector robotPosition;
        Vector ballRelativePosition;
        Vector ballPosition;

        /* -- Is at coordinate -- */
        bool isCoord = false;

        /* -- Goal Data -- */
        Vector defendGoal = Vector(0, -(FIELD_LENGTH_CM / 2) + GOAL_OFFSET_CM);
        Vector attackGoal = Vector(0, (FIELD_LENGTH_CM / 2) - GOAL_OFFSET_CM);

    private:

        /* -- Calculate new robot position -- */
        void calculateRobotPosition();

        /* -- Calculate ball position - relative & absolute - -- */
        void calculateBallPosition();

        /* -- Move between the difference of two points -- */
        bool moveByDifference(MoveData *calcMove, Vector diff);
        MoveData moveByDifference(Vector diff);

        /* -- IMU heading -- */
        float heading;

        /* -- Coordinate PID -- */
        PID coordPID = PID(TO_COORD_KP, TO_COORD_KI, TO_COORD_KD, TO_COORD_MAX_SPEED);

        /* -- Timer for new coordinate calculation -- */
        Timer newCoordTimer = Timer(NEW_COORD_TIMER);
};

extern CoordinateManager coordManager;

#endif