#ifndef DIRECTIONMANAGER_H
#define DIRECTIONMANAGER_H

#include <Arduino.h>
#include <Common.h>

#include <TSSP.h>
#include <LSArray.h>
#include <Camera.h>
#include <RoleManager.h>
#include <IMU.h>
#include <Bluetooth.h>

#include <CoordinateManager.h>


#include <MoveData.h>

#include <PID.h>

class DirectionManager{

    public:

        /* -- Class Constructor + Init -- */
        DirectionManager();

        MoveData update();

    private:

        MoveData calculateAttack();

        MoveData calculateDefend();

        MoveData calculateAvoidance(MoveData calcMove);

        MoveData calculateCorrection();







        PID headingPID = PID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);
        PID attackGoalTrackPID = PID(ATTACK_GOAL_TRACK_KP, ATTACK_GOAL_TRACK_KI, ATTACK_GOAL_TRACK_KD, ATTACK_GOAL_TRACK_MAX_CORRECTION);
        PID defendGoalTrackPID = PID(DEFEND_GOAL_TRACK_KP, DEFEND_GOAL_TRACK_KI, DEFEND_GOAL_TRACK_KD, DEFEND_GOAL_TRACK_MAX_CORRECTION);

        PID xPID = PID(X_MOVEMENT_KP, X_MOVEMENT_KI, X_MOVEMENT_KD, X_MOVEMENT_MAX);
        PID yPID = PID(Y_MOVEMENT_KP, Y_MOVEMENT_KI, Y_MOVEMENT_KD, Y_MOVEMENT_MAX);
};

extern DirectionManager directionManager;

#endif