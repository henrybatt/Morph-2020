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
    if (kickerCharge.timeHasPassedNoUpdate()){
        if (lastKick.timeHasPassed()){
            digitalWriteFast(KICKER_PIN, HIGH);
            kickerCharge.update();
        } else {
            digitalWriteFast(KICKER_PIN, LOW);
        }
    }
}


bool BallManager::hasBall(){
    // return digitalReadFast(LIGHTGATE_PIN);
    return (analogRead(LIGHTGATE_PIN) < LIGHTGATE_THRESHOLD);
}


bool BallManager::hasKicked(){
    return !lastKick.timeHasPassedNoUpdate();
}


