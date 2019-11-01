#include <CoordinateManager.h>


CoordinateManager coordManager = CoordinateManager();


CoordinateManager::CoordinateManager(){}


void CoordinateManager::update(){

    calculateRobotPosition();
    calculateBallPosition();

}


bool CoordinateManager::moveToCoord(MoveData *calcMove, Vector target){
    if (camera.goalVisible()){
        // Movement can be calculated, move by the point difference between coords
        moveByDifference(*&calcMove, target - robotPosition);
    } else {
        // Cannot calculate poisition, stop
        *calcMove = MoveData(-1, 0);
        return false;
    }
}


MoveData CoordinateManager::moveToCoord(Vector target){
    if (camera.goalVisible()){
        return moveByDifference(target - robotPosition);
    } else {
        return MoveData(-1, 0);
    }
}


bool CoordinateManager::moveByDifference(MoveData *calcMove, Vector diff){
    if (diff.mag < COORD_THRESHOLD_DISTANCE){
        // At coords, stop
        *calcMove = MoveData(-1, 0);
    } else {
        // Calculate direction towards coords
        *calcMove = MoveData(mod(diff.arg - imu.getHeading(), 360), abs(coordPID.update(diff.mag, 0)));
    }
}


MoveData CoordinateManager::moveByDifference(Vector diff){
    if (diff.mag < COORD_THRESHOLD_DISTANCE){
        // At coords, stop
        return MoveData(-1, 0);
    } else {
        // Calculate direction towards coords
        return MoveData(mod(diff.arg - imu.getHeading(), 360), abs(coordPID.update(diff.mag, 0)));
    }
}


Vector CoordinateManager::getRobotPosition(){
    return robotPosition;
}


Vector CoordinateManager::getBallPosition(){
    return ballPosition;
}


void CoordinateManager::calculateRobotPosition(){

    if (camera.goalVisible()){
        uint16_t angle = camera.attackClosest() ? camera.attack.angle : camera.defend.angle;
        angle = mod(angle + imu.getHeading(), 360);

        float distance = camera.closestCentimeter();

        // Decide if in attacking or defending side of field to determine what quadrant group were in. (Positive or negative y)
        int8_t quadrant = ((camera.attackClosest()) ? 1 : -1);

        // Robot Position calculation. Polar > Cartesian
        int8_t i = constrain(distance * -sin(toRadians(angle)), (-FIELD_WIDTH_CM / 2), (FIELD_WIDTH_CM / 2));
        int8_t j = constrain(FIELD_LENGTH_WITH_GOAL * quadrant + (distance * -cos(toRadians(angle))), (-FIELD_LENGTH_CM / 2), (FIELD_LENGTH_CM / 2));
        robotPosition = Vector(i, j);
    }
}


void CoordinateManager::calculateBallPosition(){
    ballPosition = robotPosition + tssps.data.vector(imu.getHeading());
}