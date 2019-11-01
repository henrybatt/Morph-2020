#include <DirectionManager.h>


DirectionManager directionManager = DirectionManager();


DirectionManager::DirectionManager(){

}


MoveData DirectionManager::update(){
    if (roleManager.getRole() == Role::attack){
        return calculateAvoidance(calculateAttack());
    } else if (roleManager.getRole() == Role::defend){
        return calculateAvoidance(calculateDefend());
    }
}


MoveData DirectionManager::calculateAvoidance(MoveData calcMove){

}

MoveData DirectionManager::calculateAttack(){

    if (bluetooth.otherData.ballData.isOut){
        coordManager.moveToCoord(Vector(BALL_OUT_COORD_X, BALL_OUT_COORD_Y));
    }


}


MoveData DirectionManager::calculateDefend(){

}