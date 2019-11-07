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

        CoordinateManager();

        void update(float _heading);

        bool moveToCoord(MoveData *calcMove, Vector target);
        MoveData moveToCoord(Vector target);

        Vector getRobotPosition();
        Vector getBallPosition();

        bool newCoordUpdate();

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

        float heading;

        PID coordPID = PID(TO_COORD_KP, TO_COORD_KI, TO_COORD_KD, TO_COORD_MAX_SPEED);

        Timer newCoordTimer = Timer(NEW_COORD_TIMER);
};

extern CoordinateManager coordManager;

#endif