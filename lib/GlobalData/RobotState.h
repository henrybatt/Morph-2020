#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include "Common.h"
#include "BallData.h"
#include "GoalData.h"
#include "LineData.h"
#include "MoveData.h"
#include "Vector.h"

typedef struct RobotState{

    /* -- Inputs -- */

    // Ball Inputs
    BallData ball;

    // Line Inputs
    LineData line;
    LineData avoid;

    // Goal inputs
    GoalData attackGoal;
    GoalData defendGoal;

    // Robot Position Inputs
    Vector robot;

    // IMU Inputs
    float heading;

    // Other
    bool BTConnection;
    bool otherBallIsOut;

    /* -- Outputs -- */

    // Movement Outputs
    MoveData movement;

    bool canSwitch;
    bool isAttack;
    bool ballIsOut;

} RobotState;

extern RobotState robotState;

#endif
