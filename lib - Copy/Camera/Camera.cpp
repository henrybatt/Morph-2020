#include <Camera.h>

Camera camera = Camera();

Camera::Camera(){
    cameraSerial.begin(CAM_BAUD);
    update();
}

/* - Public - */

void Camera::update(){

    newCamData = false; // Reset values
    faceGoal = false;

    if (cameraSerial.available() >= CAM_PACKET_SIZE){
        if (cameraSerial.read() == CAM_START_BYTE && cameraSerial.read() == CAM_START_BYTE){
            uint8_t dataBuffer[CAM_PACKET_SIZE - 2];
            newCamData = true;

            for (uint8_t i = 0; i < CAM_PACKET_SIZE - 2; i++){
                dataBuffer[i] = cameraSerial.read();
            }

            attack = GoalData((dataBuffer[0] << 8 | dataBuffer[1]), dataBuffer[2]);
            defend = GoalData((dataBuffer[3] << 8 | dataBuffer[4]), dataBuffer[5]);
        }
    }
}


bool Camera::goalVisible(){
    return attack.visible() || defend.visible();
}


uint8_t Camera::closestDistance(){
    if (goalVisible()){
        if (!attack.visible()){
            return defend.distance;

        } else if (!defend.visible()){
            return attack.distance;

        } else {
            return min(attack.distance, defend.distance);
        }
    }
    return 0;
}


float Camera::closestCentimeter(){
    if (goalVisible()){
        if (!attack.visible()){
            return defend.calculateCentimeter();

        } else if (!defend.visible()){
            return attack.calculateCentimeter();

        } else {
            return min(attack.calculateCentimeter(), defend.calculateCentimeter());
        }
    }
    return 0; 
}


bool Camera::attackClosest(){
    return closestDistance() == attack.distance;
}


bool Camera::newData(){
    return newCamData;
}

/* - Private - */