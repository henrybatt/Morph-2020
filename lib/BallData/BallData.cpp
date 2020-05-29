#include <BallData.h>

BallData::BallData(){}


BallData::BallData(uint16_t _angle, uint8_t _strength){
    angle = _angle;
    strength = _strength;
}

/* - Public - */

float BallData::orbitAngle(){
    float ballAngleDifference = -findSign(angle-180) * fminf(90, 0.4f * expf(ANGLE_DIFF_MULTIPLIER * smallestAngleBetween(angle, 0.0f)));
    float strengthFactor = constrain((strength - BALL_FAR_STRENGTH) / (BALL_CLOSE_STRENGTH - BALL_FAR_STRENGTH), 0, 1);
    float distanceMultiplier = constrain((DIST_MULTIPLIER_1 * strengthFactor * expf(DIST_MULTIPLIER_2 * strengthFactor)), 0, 1);
    orbitAddition = ballAngleDifference * distanceMultiplier;
    return orbitAddition;
}


bool BallData::visible(){
    return strength != 0;
}


Vector BallData::calcVectors(Vector robot, float heading){
    absPosition = robot + calcRelative(heading);
    return absPosition;
}


Vector BallData::calcRelative(float heading){
    uint16_t absAngle = floatMod(angle + heading, 360.0f);
    float distance = 123;
    relativePosition = Vector(absAngle, distance, false);
    return relativePosition;
}