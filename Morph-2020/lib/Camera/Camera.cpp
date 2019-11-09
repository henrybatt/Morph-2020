#include <Camera.h>


Camera camera = Camera();


Camera::Camera(){
    cameraSerial.begin(CAM_BAUD);
    newCamData = true;
    read();
}


void Camera::read(){
    if (cameraSerial.available() >= CAM_PACKET_SIZE){
        if (cameraSerial.read() == CAM_START_BYTE && cameraSerial.peek() == CAM_START_BYTE){
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
    goalTrack();
    
    #if DEBUG_CAMERA
        Serial.print("Camera Data:\t");
        Serial.printf("Attack Angle: %i,\t Attack Distance: %i,\t Attack Visible: %i,\t", attack.angle, attack.distance, attack.visible());
        Serial.printf("Defend Angle: %i,\t Defend Distance: %i,\t Defend Visible: %i \n", defend.angle, defend.distance, defend.visible());
    #endif

}


void Camera::goalTrack(){
    attack.face = attack.visible() ? true : false; //Set as additional value to allow manual modification
    defend.face = defend.visible() ? true : false;
}


uint8_t Camera::closestDistance(){
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
