#include <RoleManager.h>


RoleManager roleManager = RoleManager();


RoleManager::RoleManager(){
    defaultRole = ROBOT ? Role::defend : Role::attack;
    isMaster = ROBOT;
}


void RoleManager::update(){

    if (bluetooth.isConnected){

        if (currentRole == Role::undecided){
            undecidedRole();
        } else if (isMaster){
            masterSwitch();
        } else {
            pickOpposite();
        }

    } else if(bluetooth.previouslyConnected){
        currentRole = Role::defend;

    } else {
        currentRole = defaultRole;
    }
}


void RoleManager::requestSwitch(){
    requestingSwitch = true;
}


bool RoleManager::hasSwitched(){
    return !switchTimer.timeHasPassedNoUpdate();
}


bool RoleManager::isSwitching(){
    return requestingSwitch;
}


Role RoleManager::getRole(){
    return Role::attack;
    // return (currentRole == Role::undecided ? defaultRole : currentRole);
}


void RoleManager::roleLED(){
    if (getRole() == Role::attack && attackLEDTimer.timeHasPassed()){
        digitalWriteFast(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    } else if (getRole() == Role::defend && defendLEDTimer.timeHasPassed()){
        digitalWriteFast(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    } else if (getRole() == Role::undecided && undecidedLEDTimer.timeHasPassed()){
        digitalWriteFast(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }
}


void RoleManager::masterSwitch(){
    if (shouldSwitch()){
        currentRole = currentRole == Role::defend ? Role::attack : Role::defend;
    }
}


void RoleManager::pickOpposite(){
    currentRole = bluetooth.otherData.role == Role::attack ? Role::defend : Role::attack;
}


void RoleManager::undecidedRole(){
    if (bluetooth.otherData.role == Role::undecided){
        currentRole = defaultRole;
    } else {
        pickOpposite();
    }
}


bool RoleManager::shouldSwitch(){
    BluetoothData attacker = currentRole == Role::attack ? bluetooth.thisData : bluetooth.otherData;
    BluetoothData defender = currentRole == Role::defend ? bluetooth.thisData : bluetooth.otherData;

    return (angleIsInside(360 - SWITCH_DEFEND_ANGLE, SWITCH_DEFEND_ANGLE, defender.ballData.angle) && defender.ballData.strength > SWITCH_DEFEND_STRENGTH)
            && ((angleIsInside(360 - SWITCH_ATTACK_ANGLE, SWITCH_ATTACK_ANGLE, attacker.ballData.angle) && attacker.ballData.strength < SWITCH_ATTACK_STRENGTH) 
                || attacker.ballData.strength <  SWITCH_ATTACK_FAR_STRENGTH)
            && (attacker.lineData.onField() && defender.lineData.onField());
}







