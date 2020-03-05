#include <Common.h>

#include <Common.h>

int a1;
int a2;

void recieveData(){

    while(MASTER_SERIAL.available() >= SLAVE_PACKET_SIZE){
        if (MASTER_SERIAL.read() == SLAVE_START_BYTE && MASTER_SERIAL.peek() == SLAVE_START_BYTE){
            uint8_t dataBuffer[SLAVE_PACKET_SIZE - 2] = {0};

            for (uint8_t i = 0; i < SLAVE_PACKET_SIZE - 2; i++) {
                dataBuffer[i] = MASTER_SERIAL.read();
            }

            a1 = dataBuffer[0] << 8 | dataBuffer[1];
            a2 = dataBuffer[2] << 8 | dataBuffer[3];


        }
    }


}


void setup(){

    MASTER_SERIAL.begin(TEENSY_BAUD);

}


void loop(){

    recieveData();

    Serial.print(a1);
    Serial.print(", ");
    Serial.println(a2);



}