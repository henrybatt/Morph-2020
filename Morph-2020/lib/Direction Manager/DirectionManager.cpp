#include <DirectionManager.h>


DirectionManager directionManager = DirectionManager();


DirectionManager::DirectionManager(){}


void DirectionManager::updateData(BallData _ballData, LineData _lightData, float _heading){
    ballData = _ballData;
    heading = _heading;
    
    avoid.update(_lightData, ballData, heading);
    ballData.isOut = avoid.isOutsideLine(ballData.angle);

}


BluetoothData DirectionManager::packageBluetooth(){
    //BluetoothData(tssps.getBallData(), lightArray.getAvoidData(), roleManager.getRole(), bnoWrapper.getHeading(), coordManager.getRobotPosition())
    return BluetoothData(ballData, avoid.getLineData(), roleManager.getRole(), heading, coordManager.getRobotPosition());
}


MoveData DirectionManager::update(){
    if (roleManager.getRole() == Role::attack){
        return calculateCorrection(avoid.calculateAvoidance(calculateAttack()));
    } else if (roleManager.getRole() == Role::defend){
        return calculateCorrection(avoid.calculateAvoidance(calculateDefend()));
    }
    return calculateCorrection(avoid.calculateAvoidance(MoveData(-1, 0)));
}


MoveData DirectionManager::calculateAttack(){

    if (bluetooth.otherData.ballData.isOut){
        // Defender see's ball isOut, move to centre of field
        camera.attack.face = false;
        return coordManager.moveToCoord(Vector(BALL_OUT_COORD_X, BALL_OUT_COORD_Y));

    } else if (ballData.visible()){
         // Calculate Movement towards ball.
        return calculateOrbit();

    } else if (bluetooth.otherData.ballData.visible()){
        // Other Robot sees ball, move towards it
        camera.attack.face = false;
        return calculateOtherOrbit();

    } else if (camera.goalVisible()){
        // No ball, move to the centre
        camera.attack.face = false;
        return coordManager.moveToCoord(Vector(NO_BALL_COORD_X, NO_BALL_COORD_Y));
        
    } else {
        // No ball or coords, stop
        return MoveData(-1, 0);
    }

}


MoveData DirectionManager::calculateDefend(){

    if (ballData.visible()){
        
        if (angleIsInside(360 - DEFEND_CAPTURE_ANGLE, DEFEND_CAPTURE_ANGLE, ballData.angle) && ballData.strength > DEFEND_SURGE_STRENGTH && coordManager.robotPosition.j < DEFEND_SURGE_Y){
            return calculateOrbit();

        } else if (!angleIsInside(270, 90, ballData.angle)){
            // Coords for if too close to goal?
            camera.defend.face = false;
            return calculateOrbit();

        } else {
            float xMove = -xPID.update((ballData.angle > 180 ? ballData.angle - 360 : ballData.angle), 0);
            float yMove = camera.defend.visible() ? yPID.update(camera.defend.calculateCentimeter(), DEFEND_DISTANCE_CM) : -15; // This all good?
            return MoveData(floatMod(toDegrees(atan2(yMove, xMove)), 360), sqrtf(yMove * yMove + xMove * xMove));
        }
    } else if (camera.goalVisible()){
        camera.defend.face = false;
        return coordManager.moveToCoord(Vector(0, coordManager.defendGoal.j + DEFEND_DISTANCE_CM));

    } else {
        return MoveData(-1, 0);
    }
}



MoveData DirectionManager::calculateCorrection(MoveData calcMove){
    if (roleManager.getRole() == Role::attack && camera.attack.face){
        calcMove.correction = -attackGoalTrackPID.update((mod(camera.attack.angle + 180, 360) - 180), 0);
    } else if (roleManager.getRole() == Role::defend && camera.defend.face){
        calcMove.correction = -defendGoalTrackPID.update((mod(camera.defend.angle + 180, 360) - 180), 180);
    } else {
        calcMove.correction = round(imuPID.update((mod(heading + 180, 360) - 180), 0));
    }
    return calcMove;
}


MoveData DirectionManager::calculateOrbit(){
    MoveData calcMove;

    float ballAngleDifference = -findSign(ballData.angle-180) * fmin(90, 0.4 * expf(ANGLE_DIFF_MULTIPLIER * smallestAngleBetween(ballData.angle, 0)));
    float strengthFactor = constrain(((float)ballData.strength - (float)BALL_FAR_STRENGTH) / ((float)BALL_CLOSE_STRENGTH - (float)BALL_FAR_STRENGTH), 0, 1);
    float distanceMultiplier = constrain((DIST_MULTIPLIER * strengthFactor * expf(4.5 * strengthFactor)), 0, 1);
    float angleAddition = ballAngleDifference * distanceMultiplier;

    calcMove.angle = floatMod(ballData.angle + angleAddition, 360);

    //If ball infront of capture zone, surge forwards fast, else move at a modular speed
    if (ballData.strength > ATTACK_SURGE_STRENGTH && angleIsInside(360 - ATTACK_CAPTURE_ANGLE, ATTACK_CAPTURE_ANGLE, ballData.angle)){
        calcMove.speed = ORBIT_SURGE_SPEED;
        ballManager.attackKick();
    } else {
        calcMove.speed = ORBIT_SLOW_SPEED + (ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0 - abs(angleAddition) / 90.0);
    }

    #if DEBUG_ORBIT
        Serial.printf("Orbit Data:\tAngle: %i,\t Speed: %i,\t Angle Addition: %f \n", calcMove.angle, calcMove.speed, angleAddition);
    #endif

    return calcMove;
}


MoveData DirectionManager::calculateOtherOrbit(){
    MoveData calcMove;
    return calcMove;
    //Grab other robots ball ball coords using its strength, angle + position
    // Move to coordinate 

    //Figure out if other robots coord is good, send another value??

}


