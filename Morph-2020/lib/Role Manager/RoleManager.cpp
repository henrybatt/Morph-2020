#include <RoleManager.h>


RoleManager roleManager = RoleManager();


RoleManager::RoleManager(){
    defaultRole = ROBOT ? Role::defend : Role::attack;
}


void RoleManager::update(){

    Role previousRole = currentRole;

    if (bluetooth.isConnected){

        // Connected to  bluetooth, pick role
        if (currentRole == Role::undecided){
            // Undecided Role, pick default or opposite
            if (bluetooth.otherData.role == Role::undecided){
                currentRole = defaultRole;
            } else {
                currentRole = bluetooth.otherData.role == Role::defend ? Role::attack : Role::defend;
            }

        } else if (ROBOT){
            // Default role decider - Defender
            if (shouldSwitch((currentRole == Role::attack ? bluetooth.thisData : bluetooth.otherData), 
                            (currentRole == Role::defend ? bluetooth.thisData : bluetooth.otherData))){
                currentRole = currentRole == Role::defend ? Role::attack : Role::defend;
            }

        } else {
            // Opposite of default decider
            currentRole = bluetooth.otherData.role == Role::defend ? Role::attack : Role::defend;
        }

        // If statement for if become defender, move out of way

    } else if (bluetooth.previouslyConnected){
        // Was connected, other robot went offline, switch to defense
        currentRole = Role::defend;

    } else {
        // Never connected, pick default Role
        currentRole = defaultRole;
    }
}


bool RoleManager::shouldSwitch(BluetoothData attacker, BluetoothData defender){
    return (angleIsInside(360 - SWITCH_DEFEND_ANGLE, SWITCH_DEFEND_ANGLE, defender.ballData.angle) && defender.ballData.strength > SWITCH_DEFEND_STRENGTH)
            && ((angleIsInside(360 - SWITCH_ATTACK_ANGLE, SWITCH_ATTACK_ANGLE, attacker.ballData.angle) && attacker.ballData.strength < SWITCH_ATTACK_STRENGTH) 
                || attacker.ballData.strength <  SWITCH_ATTACK_FAR_STRENGTH)
            && (attacker.lineData.onField() && defender.lineData.onField());
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


Role RoleManager::getRole(){
    return (currentRole == Role::undecided ? defaultRole : currentRole);
}