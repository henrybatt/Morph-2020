#include "StatesMovement.h"


using namespace States::Movement;

PID States::Movement::idlePID = PID(IDLE_KP, IDLE_KI, IDLE_KD, IDLE_MAX_CORRECTION);
PID States::Movement::headingPID = PID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);
PID States::Movement::attackTrackPID = PID(GOAL_ATTACK_KP, GOAL_ATTACK_KI, GOAL_ATTACK_KD, GOAL_ATTACK_MAX_CORRECTION);
PID States::Movement::defendTrackPID = PID(GOAL_DEFEND_KP, GOAL_DEFEND_KI, GOAL_DEFEND_KD, GOAL_DEFEND_MAX_CORRECTION);

PID States::Movement::coordPID = PID(TO_COORD_KP, TO_COORD_KI, TO_COORD_KD, TO_COORD_MAX_SPEED);
PID States::Movement::iPID = PID(I_MOVEMENT_KP, I_MOVEMENT_KI, I_MOVEMENT_KD, I_MOVEMENT_MAX_SPEED);
PID States::Movement::jPID = PID(J_MOVEMENT_KP, J_MOVEMENT_KI, J_MOVEMENT_KD, J_MOVEMENT_MAX_SPEED);

void States::Movement::imu_correction() {
    if (robotState.movement.speed <= 0) {
        robotState.movement.correction = idlePID.update(floatMod(robotState.heading + 180.0f, 360.0f) - 180.0f, 0.0f);

    } else {
        robotState.movement.correction = headingPID.update(floatMod(robotState.heading + 180.0f, 360.0f) - 180.0f, 0.0f);
    }
}

void States::Movement::attack_correction(bool goalCorrection) {
    if (goalCorrection && robotState.attackGoal.visible()) {
        robotState.movement.correction = -attackTrackPID.update(floatMod(robotState.attackGoal.angle + 180.0f, 360.0f) - 180.0f, 0.0f);
    } else {
        imu_correction();
    }
}

void States::Movement::defend_correction(bool goalCorrection) {
    if (goalCorrection && robotState.defendGoal.visible()) {
        robotState.movement.correction = -defendTrackPID.update(floatMod(robotState.defendGoal.angle + 180.0f, 360.0f) - 180.0f, 180.0f);
    } else {
        imu_correction();
    }
}

void States::Movement::calc_orbit() {
    float ballAngleDifference = -sign(robotState.ball.angle - 180) * fminf(90, 0.4f * expf(ANGLE_DIFF_MULTIPLIER * smallestAngleBetween(robotState.ball.angle, 0.0f)));
    float strengthFactor = constrain((robotState.ball.strength - BALL_FAR_STRENGTH) / (BALL_CLOSE_STRENGTH - BALL_FAR_STRENGTH), 0, 1);
    float distanceMultiplier = constrain(DIST_MULTIPLIER_1 * strengthFactor * expf(DIST_MULTIPLIER_2 * strengthFactor), 0, 1);
    float orbitAddition = ballAngleDifference * distanceMultiplier;

    robotState.movement.angle = floatMod(robotState.ball.angle + orbitAddition, 360.0f);
    robotState.movement.speed = ORBIT_SLOW_SPEED + (ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0f - fabsf(orbitAddition) / 90.0f);
}

void States::Movement::calc_robot_positon(){
    /* - Calculate Robot Position - */
    if (robotState.attackGoal.visible() || robotState.defendGoal.visible()) {
        if (robotState.attackGoal.distance < robotState.defendGoal.distance){
            uint16_t angle = floatMod(robotState.attackGoal.angle + robotState.heading, 360.0f);
            float distance = robotState.attackGoal.calculateCentimeter();
            int8_t i = constrain(distance * -sinf(toRadians(angle)), (-FIELD_WIDTH_CM / 2), (FIELD_WIDTH_CM / 2));
            int8_t j = constrain(FIELD_LENGTH_WITH_GOAL + (distance * -cosf(toRadians(angle))), (-FIELD_LENGTH_CM / 2), (FIELD_LENGTH_CM / 2));
            robotState.robot = Vector(i, j);
        } else {
            uint16_t angle = floatMod(robotState.defendGoal.angle + robotState.heading, 360.0f);
            float distance = robotState.defendGoal.calculateCentimeter();
            int8_t i = constrain(distance * -sinf(toRadians(angle)), (-FIELD_WIDTH_CM / 2), (FIELD_WIDTH_CM / 2));
            int8_t j = constrain(-FIELD_LENGTH_WITH_GOAL + (distance * -cosf(toRadians(angle))), (-FIELD_LENGTH_CM / 2), (FIELD_LENGTH_CM / 2));
            robotState.robot = Vector(i, j);
        }
    } else {
        robotState.robot = Vector();
    }
}


void States::Movement::move_to_coord(Vector target) {
    if (robotState.attackGoal.visible() || robotState.defendGoal.visible()) {
        Vector diff = target - robotState.robot;

        if (diff.mag >= COORD_THRESHOLD_DISTANCE) {
            robotState.movement = MoveData(floatMod(diff.arg - robotState.heading, 360.0f),
                                           fabsf(coordPID.update(diff.mag, 0.0f)));
        }
    }
}

bool States::Movement::at_coord(Vector target) {
    Vector diff = target - robotState.robot;

    if (diff.mag <= COORD_THRESHOLD_DISTANCE) {
        return true;
    }

    return false;
}

float States::Movement::lerp(float inital, float final, float prog) {
    return inital + constrain(prog, 0,1) * (final - inital);
}




void States::Movement::avoidance(){
    /* - Calculate Avoidance - */
    bool onLine = (robotState.line.angle != NO_LINE_ANGLE);
    float lineAngle = onLine ? floatMod(robotState.line.angle + robotState.heading, 360.0f) : NO_LINE_ANGLE;
    float lineSize = onLine ? robotState.line.size : NO_LINE_SIZE;

    if (onLine) {
        // Seeing line determine how to return
        if (robotState.avoid.onField()) {
            // Just saw line, save avoid data
            robotState.avoid = LineData(lineAngle, lineSize);

        } else {
            if (robotState.avoid.size == 3) {
                // Was outside of line but just started touching
                robotState.avoid = LineData(floatMod(lineAngle + 180.0f, 360.0f), 2 - lineSize);

            } else {
                // Still on line, decide what side
                if (smallestAngleBetween(robotState.avoid.angle, lineAngle) <= 90.0f) {
                    // Angles between 90 degrees, inside of field, save new angle
                    robotState.avoid = LineData(lineAngle, lineSize);

                } else {
                    // Angle changed by more than 90 degrees, outside of field, modify angle
                    robotState.avoid = LineData(floatMod(lineAngle + 180.0f, 360.0f), 2 - lineSize);
                }
            }
        }
    } else {
        if (!robotState.avoid.onField()) {
            // No line but recently on
            if (robotState.avoid.size <= 1) {
                // Was inside line, returned to field
                robotState.avoid = LineData(NO_LINE_ANGLE, NO_LINE_SIZE);
            } else {
                // Was outside line, now over
                robotState.avoid.size = 3;
            }
        }
    }

    #if DEBUG_AVOIDANCE
        Serial.printf("Avoid Data:\t Angle: %i,\t Size: %f \n", robotState.avoid.angle, robotState.avoid.size);
    #endif

    /* - Calculate Return Movememnt - */
    if (!robotState.avoid.onField()){ // Not on field, move back across line
        float returnAngle = floatMod(robotState.avoid.angle + 180.0f - robotState.heading, 360.0f); // Angle to move to return to field
    
        if (robotState.avoid.size > LINE_SIZE_BIG){ // Move Back onto field directly
            robotState.movement = MoveData(returnAngle, (robotState.movement.speed == 3 ? AVOID_OVER_SPEED : robotState.avoid.size * AVOID_SPEED)); // Field return movement, speed proportional to distance over line

        } else if (robotState.avoid.size > LINE_SIZE_SMALL){ // Avoidance
            if (isOutsideLine(robotState.ball.angle) && isOutsideLine(robotState.movement.angle)){
                // Ball outside field, sit on line
                robotState.movement.speed = 0;

            } else {
                // Ball in field, decide movement
                int angleToLine = smallestAngleBetween(robotState.movement.angle, returnAngle);
                if (angleToLine < AVOID_PURSUE_ANGLE){
                    // 
                    if (angleToLine > AVOID_NORMAL_ANGLE){
                        robotState.movement = MoveData(((floatMod(returnAngle + 180.0f - robotState.movement.angle, 360.0f)) > 0 && (floatMod(returnAngle + 180.0f - robotState.movement.angle, 360.0f)) < 180.0f)
                                                    ? floatMod(returnAngle + 60.0f, 360.0f)
                                                    : floatMod(returnAngle - 60.0f, 360.0f),
                                                robotState.avoid.size * AVOID_SPEED);
                    }
                } else {
                    robotState.movement = MoveData(returnAngle, (robotState.avoid.size * AVOID_SPEED));
                }
            }
        }
    }
}

bool States::Movement::isOutsideLine(float angle) {
    if (!robotState.avoid.onField()) {
        if (floatMod(robotState.avoid.angle, 90.0f) > LINE_CORNER_ANGLE_THRESHOLD && floatMod(robotState.avoid.angle, 90.0f) > 90.0f - LINE_CORNER_ANGLE_THRESHOLD) {
            // Must be on a corner if mod of angle greater than value line curves

            // If orbit angle and line angle between 90 or 180 respectively must be trying to move out
            return (angleIsInside(floatMod(robotState.avoid.angle - 135 - LINE_BUFFER_CORNER, 360.0f), floatMod(robotState.avoid.angle + 135.0f + LINE_BUFFER_CORNER, 360.0f), floatMod(angle + robotState.heading, 360.0f)));
        } else {
            // On side of line
            return (angleIsInside(floatMod(robotState.avoid.angle - 90 - LINE_BUFFER, 360), floatMod(robotState.avoid.angle + 135 + LINE_BUFFER, 360.0f), floatMod(angle +robotState.heading, 360.f)));
        }
    }
    return false;
}