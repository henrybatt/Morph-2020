#include <Arduino.h>

#include "Camera.h"
#include "Common.h"
#include "LightArray.h"
#include "MPU.h"
#include "MotorArray.h"
#include "States.h"
#include "StatesMovement.h"
#include "TSSPArray.h"

StateMachine sm;
RobotState robotState;

void slave_recieve(){
    while(SLAVE_SERIAL.available() >= SLAVE_PACKET_SIZE){
        if (SLAVE_SERIAL.read() == SLAVE_START_BYTE && SLAVE_SERIAL.peek() == SLAVE_START_BYTE){
            uint8_t dataBuffer[SLAVE_PACKET_SIZE - 2] = {0};

            for (uint8_t i = 0; i < SLAVE_PACKET_SIZE - 2; i++) {
                dataBuffer[i] = SLAVE_SERIAL.read();
            }

            robotState.ball = BallData(word(dataBuffer[0], dataBuffer[1]),
                                word(dataBuffer[2], dataBuffer[3]));

            robotState.line = LineData(word(dataBuffer[4], dataBuffer[5]),
                                word(dataBuffer[6], dataBuffer[7]) / 100);
        }
    }
}



void setup(){
    Serial.begin(9600);
    Serial.println("Setup Complete");

    sm = StateMachine(&States::Attack::orbit);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

}


void loop(){

    for (int i = 0; i < 300; i++){
        tssp.read();
    }

    // Update Data
    tssp.update();
    lightArray.update();
    mpu.update();
    camera.update();

    // Reset Outputs
    robotState.movement = MoveData();
    robotState.canSwitch = false;

    // Update SM Data
    robotState.ball = tssp.getData();
    robotState.line = lightArray.getData();
    robotState.heading = mpu.getHeading();
    robotState.attackGoal = camera.getAttackGoal();
    robotState.defendGoal = camera.getDefendGoal();
    robotState.robot = States::Movement::calc_robot_positon();

    // Update SM
    sm.update();

    // Avoidance
    States::Movement::avoidance();

    // Move Motors
    motors.update(robotState.movement);


}