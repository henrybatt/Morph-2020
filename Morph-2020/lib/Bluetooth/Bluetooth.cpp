#include <Bluetooth.h>


Bluetooth bluetooth = Bluetooth();


Bluetooth::Bluetooth(){
    BTSerial.begin(BT_BAUD);
}


void Bluetooth::update(BluetoothData data){

    thisData = data;
    
    send();

    recieve();

}


void Bluetooth::send(){

    // Starting Bytes
    BTSerial.write(BT_START_BYTE);
    BTSerial.write(BT_START_BYTE);

    // Ball Angle
    BTSerial.write((thisData.ballData.angle >> 8) & 0xFF);
    BTSerial.write(thisData.ballData.angle & 0xFF);

    // Ball Strength
    BTSerial.write((thisData.ballData.strength >> 8) & 0xFF);
    BTSerial.write(thisData.ballData.strength & 0xFF);

    // Ball Out
    BTSerial.write(thisData.ballData.isOut);

    // on Field
    BTSerial.write(!thisData.lineData.onField());

    // Role
    BTSerial.write(thisData.role);

    // Heading
    BTSerial.write((thisData.heading >> 8) & 0xFF);
    BTSerial.write(thisData.heading & 0xFF);

    // Robot Position
    BTSerial.write(((int8_t)thisData.robotPosition.i >> 8) & 0xFF);
    BTSerial.write((int8_t)thisData.robotPosition.i & 0xFF);

    BTSerial.write(((int8_t)thisData.robotPosition.j >> 8) & 0xFF);
    BTSerial.write((int8_t)thisData.robotPosition.j & 0xFF);

}


void Bluetooth::recieve(){

    bool recievedData = false;

    while (BTSerial.available() >= BT_PACKET_SIZE){

        if (BTSerial.read() == BT_START_BYTE && BTSerial.peek() == BT_START_BYTE){
            uint8_t bluetoothBuffer[BT_PACKET_SIZE - 2];
            BTSerial.read();
            for (uint8_t i = 0; i < BT_PACKET_SIZE - 2; i++){   
                bluetoothBuffer[i] = BTSerial.read();
            }

            recievedData = true;
            disconnectTimer.update();

            otherData.ballData = BallData((bluetoothBuffer[0] << 8) | bluetoothBuffer[1], (bluetoothBuffer[2] << 8) | bluetoothBuffer[3], bluetoothBuffer[4]);
            otherData.lineData = LineData(-1, bluetoothBuffer[5]);
            otherData.role = static_cast<Role>(bluetoothBuffer[6]);
            otherData.heading = (bluetoothBuffer[7] << 8 | bluetoothBuffer[8]);
            otherData.robotPosition = Vector((int8_t)(bluetoothBuffer[9] << 8 | bluetoothBuffer[10]), (int8_t)(bluetoothBuffer[11] << 8 | bluetoothBuffer[12]));


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


BluetoothData Bluetooth::getThisData(){
    return thisData;
}



BluetoothData Bluetooth::getOtherData(){
    return otherData;
}
