#include "States.h"
#include "StatesMovement.h"

using namespace States::Attack;



Idle States::Attack::idle = Idle();
Orbit States::Attack::orbit = Orbit();
BallHandle States::Attack::ballHandle = BallHandle();


/* -- Attack Idle State -- */
Idle::Idle() : State("Attack Idle State") {}

void Idle::update(){

    /* - State Setup - */
    robotState.isAttack = true;
    robotState.canSwitch = true;
    Movement::imu_correction();
    timer_manager();

    /* - State Criteria - */
    if (robotState.ball.visible()){ // Ball is visible, revert
        SM_REVERT;
    }

    /* - State Functions - */
    Movement::move_to_coord(CENTER_COORD);

}


/*-- Attack Orbit State -- */
Orbit::Orbit() : State("Attack Orbit State") {}

void Orbit::update(){

    robotState.isAttack = true;
    robotState.canSwitch = true;
    timer_manager();
    Movement::attack_correction(
        angleIsInside(360 - ATTACK_CORRECT_ANGLE, ATTACK_CORRECT_ANGLE, robotState.attackGoal.angle));


    if (!robotState.ball.visible()) { // Ball not visible, break
        Timers::attackIdleTimer->Start();
        SM_MOTOR_BRAKE;
    } else if (robotState.ball.strength >= ATTACK_SURGE_STRENGTH &&
               angleIsInside(360 - ATTACK_CAPTURE_ANGLE, ATTACK_CAPTURE_ANGLE, robotState.ball.angle)) { // We are behind the ball, surge
        SM_CHANGE_STATE_ATTACK(ballHandle);
    }

    Movement::calc_orbit();
}


/* -- Attack Ball Handle State -- */
BallHandle::BallHandle() : State("Attack Ball Handle State") {}

void BallHandle::enter(){
    accelProg = 0.0f;
    accelStart = robotState.movement.speed;
}

void BallHandle::update(){
    robotState.isAttack = true;
    robotState.canSwitch = false;
    timer_manager();
    Movement::attack_correction();
    
    if (robotState.ball.visible()) {
        if (canKick && lightgate_break()) {  // We are able to kick and ball is inside capture zone, kick
            SM_CHANGE_STATE_GLOBAL(kick);

        } else if (!angleIsInside(360 - ATTACK_CAPTURE_ANGLE, ATTACK_CAPTURE_ANGLE, robotState.ball.angle)) {  // Ball not infront, revert state
            SM_REVERT;
        }
    } else {  // Ball not visible, break
        Timers::attackIdleTimer->Start();
        SM_MOTOR_BRAKE;
    }

    robotState.movement.angle = robotState.ball.angle;
    robotState.movement.speed = Movement::lerp(accelStart, ORBIT_SURGE_SPEED, accelProg);
    accelProg += (accelProg >= 1 ? 0 : ATTACK_LERP_ACCEL_PROG);
}