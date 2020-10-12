#include "States.h"
#include "StatesMovement.h"

using namespace States::Defence;

Idle States::Defence::idle = Idle();
Defend States::Defence::defend = Defend();
Search States::Defence::search = Search();
Surge States::Defence::surge = Surge();


/* -- Defence Idle State -- */
Idle::Idle() : State("Defence Idle State") {}

void Idle::update(){
    robotState.isAttack = false;
    robotState.canSwitch = false;
    Movement::defend_correction();
    timer_manager();

    if (!robotState.defendGoal.visible()) { // No goal, look
        SM_CHANGE_STATE_DEFEND(search);
    } else if (robotState.ball.visible()) { // Ball visible, defend
        SM_CHANGE_STATE_DEFEND(defend);
    }

    // Center
    Movement::move_to_coord(Vector(0.0f, DEFEND_GOAL_J + DEFEND_DISTANCE_CM));
}


/* -- Defence Defend State -- */
Defend::Defend() : State("Defence Defend State") {}

void Defend::update(){
    robotState.isAttack = false;
    robotState.canSwitch = false;
    Movement::defend_correction();
    timer_manager();

    if (!robotState.defendGoal.visible()) {  // Cannot see goal, search for it
        SM_CHANGE_STATE_DEFEND(search);
    } else if (!robotState.ball.visible()) {  // Cannot see ball, center
        SM_CHANGE_STATE_DEFEND(idle);
    } else if (angleIsInside(360.0f - DEFEND_CAPTURE_ANGLE, DEFEND_CAPTURE_ANGLE, robotState.ball.angle) && robotState.ball.strength >= DEFEND_SURGE_STRENGTH && robotState.robot.j < DEFEND_SURGE_J) {  // Ball is infront, surge
        SM_CHANGE_STATE_DEFEND(surge);
    }


    if (!angleIsInside(360.0f - DEFEND_ANGLE, DEFEND_ANGLE, robotState.ball.angle)) {  // Ball is behind, orbit
        Movement::calc_orbit();
    } else {
        float iMove = -Movement::iPID.update((robotState.ball.angle > 180.0f ? robotState.ball.angle - 360.0f : robotState.ball.angle), 0.0f);  // Position behind ball
        float jMove = Movement::jPID.update(robotState.defendGoal.calculateCentimeter(), DEFEND_DISTANCE_CM);                                   // Position away from goal

        robotState.movement.angle = fmodf(toDegrees(atan2f(iMove, jMove)), 360.0f);
        robotState.movement.speed = sqrtf(iMove * iMove + jMove * jMove);
    }
}


/* -- Defence Search State -- */
Search::Search() : State("Defence Search State") {}

void Search::update(){
    robotState.isAttack = false;
    robotState.canSwitch = false;
    Movement::defend_correction(false);
    timer_manager();

    if (robotState.defendGoal.visible()) {
        SM_CHANGE_STATE_DEFEND(defend);
    }


    if (!angleIsInside(360.0f - DEFEND_ANGLE, DEFEND_ANGLE, robotState.ball.angle)) {  // Ball is behind, orbit around
        Movement::calc_orbit();

    } else {                                                                                                                          // Defend ball whilst moving backwards
        float iMove = -Movement::iPID.update((robotState.ball.angle > 180.0f ? robotState.ball.angle - 360.0f : robotState.ball.angle), 0.0f);  // Position behind ball
        float jMove = DEFEND_SEARCH_REVERSE;                                                                                          // Move back towards goal
        robotState.movement.angle = fmodf(toDegrees(atan2f(iMove, jMove)), 360.0f);
        robotState.movement.speed = sqrtf(iMove * iMove + jMove * jMove);
    }
}


/* -- Defence Surge State -- */
Surge::Surge() : State("Defence Surge State") {}

void Surge::enter(){
    accelProg = 0.0f;
}

void Surge::update(){
    robotState.isAttack = false;
    robotState.canSwitch = true;
    Movement::defend_correction();
    timer_manager();

    if (robotState.robot.j >= DEFEND_SURGE_J || !robotState.defendGoal.visible()) {  // Too far away from goal, or lost vision, switch to defend
        SM_CHANGE_STATE_DEFEND(defend);
    } else if (!robotState.ball.visible() || (360.0f - DEFEND_CAPTURE_ANGLE, DEFEND_CAPTURE_ANGLE, robotState.ball.angle)) {  // Ball is not visible, or not inside capture zone
        SM_CHANGE_STATE_DEFEND(defend);
    }

    if (!robotState.BTConnection && canKick && lightgate_break()) {  // We are alone and able to kick
        SM_CHANGE_STATE_GLOBAL(kick);
    }


    // YEET
    robotState.movement.angle = robotState.ball.angle;
    robotState.movement.speed = Movement::lerp(ORBIT_SLOW_SPEED, ORBIT_SURGE_SPEED, accelProg);
    accelProg += (accelProg >= 1 ? 0 : DEFEND_LERP_ACCEL_PROG);
}