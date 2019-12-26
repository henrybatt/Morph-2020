#include <CoordinateManager.h>

//

CoordinateManager::CoordinateManager(){}

/* - Public - */

void CoordinateManager::update(BallData ballData, float _heading,){

    heading = _heading;

    /* - Relative Ball Position - */
    ballRelativePosition = ballData.vector();

    if (camera.goalVisible()){
        newCoordTimer.update();

        /* - Robot Position - */
        uint16_t angle = camera.attackClosest() ? camera.attack.angle : camera.defend.angle;
        angle = mod(angle + heading, 360);

        float distance = camera.closestCentimeter();

        // Decide if in attacking or defending side of field to determine what quadrant group were in. (Positive or negative y)
        int8_t quadrant = (camera.attackClosest()) ? 1 : -1;

        // Robot Position calculation. Polar > Cartesian
        int8_t i = constrain(-distance * sinf(toRadians(angle)), (-FIELD_WIDTH_CM / 2), (FIELD_WIDTH_CM / 2));
        int8_t j = constrain(FIELD_LENGTH_WITH_GOAL * quadrant - (distance * cosf(toRadians(angle))), (-FIELD_LENGTH_CM / 2), (FIELD_LENGTH_CM / 2));
        robotPosition = Vector(i, j);

        /* - Absolute Ball Position - */
        ballPosition = robotPosition + ballRelativePosition;
    }

    #if DEBUG_POSITION
        Serial.print("Position Data: \t");
        Serial.printf("Robot: %i, %i \t", robotPosition.i, robotPosition.j);
        Serial.printf("Abs Ball: %i, %i \t", ballPosition.i, ballPosition.j);
        Serial.printf("Rel Ball: %i, %i \n", ballRelativePosition.i, ballRelativePosition.j);
    #endif
}


MoveData CoordinateManager::moveToCoord(Vector target){
    if (camera.goalVisible()) {
        return moveByDifference(target - robotPosition);
    } else {
        return MoveData(-1, 0);
    }
}


bool CoordinateManager::moveToCoord(MoveData *calcMove, Vector target){
    if (camera.goalVisible()){
        return moveByDifference(*&calcMove, target - robotPosition);
    } else {
        *calcMove = MoveData(-1, 0);
        return false;
    }
}


Vector CoordinateManager::getRobotPosition(){
    return robotPosition;
}


Vector CoordinateManager::getBallPosition(){
    return ballPosition;
}


bool CoordinateManager::newCoordUpdate(){
    return !newCoordTimer.timeHasPassedNoUpdate();
}

/* - Private - */

MoveData CoordinateManager::moveByDifference(Vector diff){
    if (diff.mag < COORD_THRESHOLD_DISTANCE){
        return MoveData(-1, 0);
    } else {
        return MoveData(floatMod(diff.arg - heading, 360), abs(coordPID.update(diff.mag, 0)))
    }
}


bool CoordinateManager::moveByDifference(MoveData *calcMove, Vector diff){
    if (diff.mag < COORD_THRESHOLD_DISTANCE){
        *calcMove =  MoveData(-1, 0);
        return true;
    } else {
        *calcMove =  MoveData(floatMod(diff.arg - heading, 360), abs(coordPID.update(diff.mag, 0)));
        return false;
    }
}