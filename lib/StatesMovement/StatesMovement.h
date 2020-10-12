#ifndef STATESMOVEMENT_H
#define STATESMOVEMENT_H

#include <Arduino.h>
#include "Common.h"
// #include "States.h"
#include "PID.h"
#include "RobotState.h"

namespace States {

    namespace Movement {

        extern PID idlePID;
        extern PID headingPID;
        extern PID attackTrackPID;
        extern PID defendTrackPID;

        extern PID coordPID;
        extern PID iPID;
        extern PID jPID;

        void imu_correction();

        void attack_correction(bool goalCorrection=true);
        void defend_correction(bool goalCorrection=true);

        void calc_orbit();


        void calc_robot_positon();
        void move_to_coord(Vector target);
        bool at_coord(Vector target);

        float lerp(float initial, float final, float prog);

        void avoidance();

        bool isOutsideLine(float angle);

    }
}

#endif