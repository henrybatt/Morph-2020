#include <DirectionManager.h>


DirectionManager directionManager = DirectionManager();


DirectionManager::DirectionManager(){

}


MoveData DirectionManager::update(BallData _ballData, float _heading){
    ballData = _ballData;
    heading = _heading;

    if (roleManager.getRole() == Role::attack){
        return calculateCorrection(calculateAvoidance(calculateAttack()));
    } else if (roleManager.getRole() == Role::defend){
        return calculateCorrection(calculateAvoidance(calculateDefend()));
    }
    return calculateCorrection(calculateAvoidance(MoveData(-1, 0)));
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

    } else {
        // No ball, move to the centre
        camera.attack.face = false;
        return coordManager.moveToCoord(Vector(NO_BALL_COORD_X, NO_BALL_COORD_Y));
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


MoveData DirectionManager::calculateAvoidance(MoveData calcMove){
    LineData lineData = lightArray.getLineData(); 

    float returnAngle = floatMod(lineData.angle + 180 - heading, 360);

    if (!lineData.onField()){
        // Not on the field, calculate return
        if (lineData.state >= 2){
            // Over other side of the line, move back across
            return MoveData(returnAngle, AVOID_RETURN_SPEED);

        } else {
            // On inside on line, calculate bounce direction

            if (lightArray.isOutsideLine(calcMove.angle)){
                // Ball is outside line, stop
                return MoveData(-1, 0);

            } else {
                // Ball is inside field
                if (smallestAngleBetween(calcMove.angle, returnAngle) < AVOID_BOUNCE_ANGLE){
                // If ball is within boucing angles decide if to move direct or bounce
                    if (smallestAngleBetween(calcMove.angle, returnAngle) < AVOID_NORMAL_ANGLE){
                        // Withing direct return angle
                        return calcMove;
                    }else{
                        // Bounce towards ball
                        return MoveData(calculateAvoianceBounce(calcMove.angle, returnAngle), AVOID_BOUNCE_SPEED);
                    }
                } else {
                    return MoveData(returnAngle, AVOID_OTHER_SPEED);
                }
            }
        }
        return MoveData(returnAngle, AVOID_OTHER_SPEED); // Somehow there was an error, just move off line
    }
    return calcMove;
}


MoveData DirectionManager::calculateCorrection(MoveData calcMove){
    if (roleManager.getRole() == Role::attack && camera.attack.face){
        calcMove.correction = -attackGoalTrackPID.update((mod(camera.attack.angle + 180, 360) - 180), 0);
    } else if (roleManager.getRole() == Role::defend && camera.defend.face){
        calcMove.correction = -defendGoalTrackPID.update((mod(camera.defend.angle + 180, 360) - 180), 180);
    } else {
        calcMove.correction = imuPID.update((mod(heading + 180, 360) - 180), 0);
    }
    return calcMove;
}


MoveData DirectionManager::calculateOrbit(){
    MoveData calcMove;

    calcMove.angle = floatMod(ballData.angle + tssps.calculateAngleAddition(), 360);

    //If ball infront of capture zone, surge forwards fast, else move at a modular speed
    if (ballData.strength > ATTACK_SURGE_STRENGTH && angleIsInside(360 - ATTACK_CAPTURE_ANGLE, ATTACK_CAPTURE_ANGLE, ballData.angle)){
        calcMove.speed = ORBIT_SURGE_SPEED;
        ballManager.attackKick();

    } else {
        calcMove.speed = ORBIT_SLOW_SPEED + (ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0 - abs(tssps.getAngleAddition()) / 90.0);
    }

    #if DEBUG_ORBIT
        Serial.printf("Orbit Data:\tAngle: %i,\t Speed: %i,\t Angle Addition: %f \n", calcMove.angle, calcMove.speed, tssps.getAngleAddition());
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


float DirectionManager::calculateAvoianceBounce(float orbitAngle, float lineAngle){
    return ((floatMod(lineAngle + 180 - orbitAngle, 360)) > 0 && (floatMod(lineAngle + 180 - orbitAngle, 360)) < 180) 
                ? floatMod(lineAngle + 60, 360) : floatMod(lineAngle - 60, 360);
}

