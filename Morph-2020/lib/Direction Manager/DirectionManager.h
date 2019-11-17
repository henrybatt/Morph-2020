#ifndef DIRECTIONMANAGER_H
#define DIRECTIONMANAGER_H

#include <Arduino.h>
#include <Common.h>

#include <TSSP.h>
#include <LSArray.h>
#include <Camera.h>
#include <RoleManager.h>
#include <Bluetooth.h>
#include <BallManager.h>
#include <CoordinateManager.h>

#include <LineData.h>
#include <MoveData.h>

#include <PID.h>

class DirectionManager{

    public:

        /* -- Class Constructor + Init -- */
        DirectionManager();

        /* --  -- */
        MoveData update(BallData _ballData, float _heading);

    private:

        /* -- Calculate orbits towards ball -- */
        MoveData calculateOrbit();
        MoveData calculateOtherOrbit();

        /* -- Calculate attacking move data -- */
        MoveData calculateAttack();

        /* -- Calculate defending move data -- */
        MoveData calculateDefend();

        /* -- Calculate how to return from line -- */
        MoveData calculateAvoidance(MoveData calcMove);

        /* -- Calculate correction -- */
        MoveData calculateCorrection(MoveData calcMove);

        /* -- Calculate Avoidance Bounce -- */
        MoveData calculateAvoianceBounce(MoveData calcMove, float returnAngle, float lineSize);

        /* -- Avoidance bounce angle -- */
        float calculateAvoianceBounceAngle(float orbitAngle, float lineAngle);

        float heading; // IMU heading
        BallData ballData; // Tssp ball data

        /* -- Movement PIDs -- */
        PID imuPID = PID(IMU_KP, IMU_KI, IMU_KD, IMU_MAX_CORRECTION);
        PID attackGoalTrackPID = PID(ATTACK_GOAL_TRACK_KP, ATTACK_GOAL_TRACK_KI, ATTACK_GOAL_TRACK_KD, ATTACK_GOAL_TRACK_MAX_CORRECTION);
        PID defendGoalTrackPID = PID(DEFEND_GOAL_TRACK_KP, DEFEND_GOAL_TRACK_KI, DEFEND_GOAL_TRACK_KD, DEFEND_GOAL_TRACK_MAX_CORRECTION);

        PID xPID = PID(X_MOVEMENT_KP, X_MOVEMENT_KI, X_MOVEMENT_KD, DEFEND_SPEED);
        PID yPID = PID(Y_MOVEMENT_KP, Y_MOVEMENT_KI, Y_MOVEMENT_KD, DEFEND_SPEED);
};

extern DirectionManager directionManager;

#endif