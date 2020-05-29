#include <Camera.h>

Camera camera = Camera();

Camera::Camera(){
    CAM_SERIAL.begin(CAM_BAUD);
}

/* - Public - */

Vector Camera::update(float heading){

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

            /* - Calculate Robot Position - */
            if (attack.visible() || defend.visible()) {
                uint16_t angle = floatMod((attack.distance < defend.distance ? attack.angle : defend.angle) + heading, 360.0f);
                float distance = fminf(attack.calculateCentimeter(), defend.calculateCentimeter());

                int8_t i = constrain(distance * -sinf(toRadians(angle)), (-FIELD_WIDTH_CM / 2), (FIELD_WIDTH_CM / 2));
                int8_t j = constrain(FIELD_LENGTH_WITH_GOAL * (attack.distance < defend.distance ? 1 : -1) + (distance * -cosf(toRadians(angle))), (-FIELD_LENGTH_CM / 2), (FIELD_LENGTH_CM / 2));
                robotPosition = Vector(i, j);
            } else {
                robotPosition = Vector();
            }
        }
    }
    return robotPosition;
}




/* - Private - */