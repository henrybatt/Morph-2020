#include <BallManager.h>


BallManager ballManager = BallManager();


BallManager::BallManager(){
    pinMode(KICKER_PIN, OUTPUT);
    digitalWriteFast(KICKER_PIN, LOW);
}


void BallManager::kickBall(){
    if (hasBall()){
        kick();
    }
}


void BallManager::attackKick(){
    if (angleIsInside(360 - KICKER_GOAL_ANGLE, KICKER_GOAL_ANGLE, camera.attack.angle) && coordManager.robotPosition.j > 0){
        kickBall();
    }
}


void BallManager::kick(){
    if (kickDischarge.timeHasPassed()){
        digitalWriteFast(KICKER_PIN, lastKick.timeHasPassed());
    }
}


bool BallManager::hasBall(){
    return (analogRead(LIGHTGATE_PIN) < LIGHTGATE_THRESHOLD);
}


bool BallManager::hasKicked(){
    return !lastKick.timeHasPassedNoUpdate();
}


