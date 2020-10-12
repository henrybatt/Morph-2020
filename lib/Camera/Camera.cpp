#include <Camera.h>

Camera camera = Camera();

Camera::Camera(){
    CAM_SERIAL.begin(CAM_BAUD);
}

/* - Public - */

void Camera::update(){

    while (CAM_SERIAL.available() >= CAM_PACKET_SIZE){
        if (CAM_SERIAL.read() == CAM_START_BYTE && CAM_SERIAL.peek() == CAM_START_BYTE){
            CAM_SERIAL.read();
            uint8_t dataBuffer[CAM_PACKET_SIZE - 2];

            for (uint8_t i = 0; i < CAM_PACKET_SIZE - 2; i++){
                dataBuffer[i] = CAM_SERIAL.read();
            }

            /* - Save Goal Data - */
            attack = GoalData(word(dataBuffer[0], dataBuffer[1]), dataBuffer[2]);
            defend = GoalData(word(dataBuffer[3], dataBuffer[4]), dataBuffer[5]);
        }
    }
}


GoalData Camera::getAttackGoal(){
    return attack;
}


GoalData Camera::getDefendGoal(){
    return defend;
}



/* - Private - */