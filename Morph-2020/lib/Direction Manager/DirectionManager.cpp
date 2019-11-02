#include <DirectionManager.h>


DirectionManager directionManager = DirectionManager();


DirectionManager::DirectionManager(){

}


MoveData DirectionManager::update(){
    if (roleManager.getRole() == Role::attack){
        return calculateCorrection(calculateAvoidance(calculateAttack()));
    } else if (roleManager.getRole() == Role::defend){
        return calculateCorrection(calculateAvoidance(calculateDefend()));
    }
}


MoveData DirectionManager::calculateAttack(){

    if (bluetooth.otherData.ballData.isOut){
        // Defender see's ball isOut, move to centre of field
        camera.attack.face = false;
        return coordManager.moveToCoord(Vector(BALL_OUT_COORD_X, BALL_OUT_COORD_Y));

    } else if (tssps.data.visible()){
         // Calculate Movement towards ball.
        return calculateOrbit();

    } else if (bluetooth.isConnected && bluetooth.otherData.ballData.visible()){
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

    if (tssps.data.visible()){
        
        if (angleIsInside(360 - DEFEND_CAPTURE_ANGLE, DEFEND_CAPTURE_ANGLE, tssps.data.angle) && tssps.data.strength > DEFEND_SURGE_STRENGTH && coordManager.robotPosition.j < DEFEND_SURGE_Y){
            return calculateOrbit();

        } else if (!angleIsInside(270, 90, tssps.data.angle)){
            // Coords for if too close to goal?
            camera.defend.face = false;
            return calculateOrbit();

        } else {
            float xMove = -xPID.update((tssps.data.angle > 180 ? tssps.data.angle - 360 : tssps.data.angle), 0);
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
    return calcMove;
}


MoveData DirectionManager::calculateCorrection(MoveData calcMove){
    if (roleManager.getRole() == Role::attack && camera.attack.face){
        calcMove.correction = -attackGoalTrackPID.update((camera.attack.angle > 180 ? camera.attack.angle - 360 : camera.attack.angle), 0);
    } else if (roleManager.getRole() == Role::defend && camera.defend.face){
        calcMove.correction = -defendGoalTrackPID.update((camera.defend.angle > 180 ? camera.defend.angle - 360 : camera.defend.angle), 180);
    } else {
        calcMove.correction = imuPID.update((imu.getHeading() > 180 ? imu.getHeading() - 360 : imu.getHeading()), 0);
    }
    return calcMove;
}


MoveData DirectionManager::calculateOrbit(){
    MoveData calcMove;

    calcMove.angle = floatMod(tssps.data.angle + tssps.calculateAngleAddition(), 360);

    //If ball infront of capture zone, surge forwards fast, else move at a modular speed
    if (tssps.data.strength > ATTACK_SURGE_STRENGTH && angleIsInside(360 - ATTACK_CAPTURE_ANGLE, ATTACK_CAPTURE_ANGLE, tssps.data.angle)){
        calcMove.speed = ORBIT_SURGE_SPEED;
        ballManager.attackKick();

    } else {
        calcMove.speed = ORBIT_SLOW_SPEED + (ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0 - abs(tssps.getAngleAddition()) / 90.0);
    }

    return calcMove;
}


MoveData DirectionManager::calculateOtherOrbit(){
    MoveData calcMove;
    return calcMove;
    //Grab other robots ball ball coords using its strength, angle + position
    // Move to coordinate 

    //Figure out if other robots coord is good, send another value??

}