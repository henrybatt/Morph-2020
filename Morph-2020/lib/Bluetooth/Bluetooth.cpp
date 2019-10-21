#include <Bluetooth.h>


void Bluetooth::init(){
    BTSerial.begin(BT_BAUD);
}

void Bluetooth::update(Role *role, BluetoothData data){

    thisData = data;
    
    send();

    recieve();

    updateRole(*&role);

}


void Bluetooth::send(){

    // Starting Byte
    BTSerial.write(BT_START_BYTE);

    // Ball Angle
    BTSerial.write(highByte(thisData.ballData.angle));
    BTSerial.write(lowByte(thisData.ballData.angle));

    // Ball Strength
    BTSerial.write(highByte(thisData.ballData.strength));
    BTSerial.write(lowByte(thisData.ballData.strength));

    // Ball Out
    BTSerial.write(thisData.ballData.isOut);

    // OnField
    BTSerial.write(thisData.lineData.onField);

    // *role
    BTSerial.write(thisData.role);

    // Robot Position
    BTSerial.write(highByte(round(thisData.robotPosition.i)));
    BTSerial.write(lowByte(round(thisData.robotPosition.i)));

    BTSerial.write(highByte(round(thisData.robotPosition.j)));
    BTSerial.write(lowByte(round(thisData.robotPosition.j)));

    // Heading
    BTSerial.write(highByte(thisData.heading));
    BTSerial.write(lowByte(thisData.heading));

}


void Bluetooth::recieve(){

    bool recievedData = false;


    while (BTSerial.available() >= BT_PACKET_SIZE){

        if (BTSerial.read() == BT_START_BYTE){
            uint8_t bluetoothBuffer[BT_PACKET_SIZE - 1];

            for (int i = 0; i < BT_PACKET_SIZE - 1; i++){
                bluetoothBuffer[i] = BTSerial.read();
            }

            recievedData = true;
            disconnectTimer.update();

            otherData.ballData = BallData((bluetoothBuffer[0] << 8) | bluetoothBuffer[1], (bluetoothBuffer[2] << 8) | bluetoothBuffer[3], bluetoothBuffer[4]);
            otherData.lineData = LineData(-1, 0, bluetoothBuffer[5]);
            otherData.role = static_cast<Role>(bluetoothBuffer[6]);
            otherData.robotPosition = Vector((bluetoothBuffer[7] << 8 | bluetoothBuffer[8]), (bluetoothBuffer[9] << 8 | bluetoothBuffer[10]));
            otherData.heading = (bluetoothBuffer[11] << 8 | bluetoothBuffer[12]);

        }
    }

    isConnected = recievedData || !disconnectTimer.timeHasPassedNoUpdate();

    if (isConnected){
        if (!previouslyConnected){
            previouslyConnected = true;
        }
    } else {
        otherData = BluetoothData();
    }
}


void Bluetooth::updateRole(Role *calcRole){

    Role role = *calcRole;

    Role previousRole = role;

    if (isConnected){

        // Connected to  bluetooth, pick role
        if (role == Role::undecided){
            // Undecided Role, pick default or opposite
            if (otherData.role == Role::undecided){
                *calcRole = defaultRole;
            } else {
                *calcRole = otherData.role == Role::defend ? Role::attack : Role::defend;
            }

        } else if (ROBOT){
            // Default *role decider - Defender
            if (shouldSwitch((role == Role::attack ? thisData : otherData), 
                                (role == Role::defend ? thisData : otherData))){
                *calcRole = role == Role::defend ? Role::attack : Role::defend;
            }

        } else {
            // Opposite of default decider
            *calcRole = otherData.role == Role::defend ? Role::attack : Role::defend;

        }

        // If statement for if become defender, move out of way

    } else if (previouslyConnected){
        // Was connected, other robot went offline, switch to defense
        *calcRole = Role::defend;

    } else {
        // Never connected, pick default Role
        *calcRole = defaultRole;
    }
}


bool Bluetooth::shouldSwitch(BluetoothData attacker, BluetoothData defender){
    return (angleIsInside(360 - SWITCH_DEFEND_ANGLE, SWITCH_DEFEND_ANGLE, defender.ballData.angle) && defender.ballData.strength > SWITCH_DEFEND_STRENGTH)
            && ((angleIsInside(360 - SWITCH_ATTACK_ANGLE, SWITCH_ATTACK_ANGLE, attacker.ballData.angle) && attacker.ballData.strength < SWITCH_ATTACK_STRENGTH) 
                || attacker.ballData.strength <  SWITCH_ATTACK_FAR_STRENGTH)
            && (attacker.lineData.onField && defender.lineData.onField);
}