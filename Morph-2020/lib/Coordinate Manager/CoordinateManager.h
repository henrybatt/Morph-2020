#ifndef COORDINATEMANAGER_H
#define COORDINATEMANAGER_H

#include <Arduino.h>
#include <Common.h>

#include <TSSP.h>
#include <Camera.h>
#include <IMU.h>

#include <MoveData.h>
#include <Vector.h>
#include <PID.h>

class CoordinateManager{

    public:

        CoordinateManager();

        void update();

        bool moveToCoord(MoveData *calcMove, Vector target);
        MoveData moveToCoord(Vector target);

        Vector getRobotPosition();
        Vector getBallPosition();

        Vector robotPosition;
        Vector ballRelativePosition;
        Vector ballPosition;

        bool isCoord = false;

        // Goal Coordinates
        Vector defendGoal = Vector(0, -(FIELD_LENGTH_CM / 2) + GOAL_OFFSET_CM);
        Vector attackGoal = Vector(0, (FIELD_LENGTH_CM / 2) - GOAL_OFFSET_CM);

    private:

        void calculateRobotPosition();

        void calculateBallPosition();

        bool moveByDifference(MoveData *calcMove, Vector diff);
        MoveData moveByDifference(Vector diff);

        PID coordPID = PID(TO_COORD_KP, TO_COORD_KI, TO_COORD_KD, TO_COORD_MAX_SPEED);
};

extern CoordinateManager coordManager;

#endif