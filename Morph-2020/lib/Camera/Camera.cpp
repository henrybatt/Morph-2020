#include <Camera.h>

Camera camera = Camera();

void Camera::init(){
    cameraSerial.begin(CAM_BAUD);
    newCamData = true;
    read();
}


void Camera::read(){
    if (cameraSerial.available() >= CAM_PACKET_SIZE){
        if (cameraSerial.read() == CAM_START_BYTE, cameraSerial.peek() == CAM_START_BYTE){
            newCamData = true;
            cameraSerial.read();
            uint8_t camBuffer[CAM_PACKET_SIZE - 2];

            for (uint8_t i = 0; i < CAM_PACKET_SIZE - 2; i++){
                camBuffer[i] = cameraSerial.read();
            }
            
            attack = GoalData(camBuffer[0] << 8 | camBuffer[1], camBuffer[2]);
            defend = GoalData(mod((camBuffer[3] << 8 | camBuffer[4]), 360), camBuffer[5]);

        }
    }
}


void Camera::update(){
    read();

    #if DEBUG_CAMERA
        Serial.print("Attack Angle: ");
        Serial.print(attack.angle);
        Serial.print(", Attack distance: ");
        Serial.print(attack.distance);
        Serial.print(", Attack visible: ");
        Serial.print(attack.visible);
        Serial.print(", Defend Angle: ");
        Serial.print(defend.angle);
        Serial.print(", Defend distance: ");
        Serial.print(defend.distance);
        Serial.print(", Defend visible: ");
        Serial.println(defend.visible);
    #endif

}


void Camera::goalTrack(){
    attack.face = attack.visible() ? true : false; //Set as additional value to allow manual modification
    defend.face = defend.visible() ? true : false;
}


int Camera::closestDistance(){
    if(attack.visible()|| defend.visible()){
        if(!attack.visible()){
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
    if(attack.visible() || defend.visible()){
        if(!attack.visible()){
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


bool Camera::goalVisible(){
    return (attack.visible() || defend.visible()); 
}


bool Camera::newData(){
    bool data = newCamData;
    newCamData = false;

    return data;
}
