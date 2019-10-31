#include <LSArray.h>


LSArray lightArray = LSArray();


LSArray::LSArray(){
    for (uint8_t i = 0; i < 4; i++){
        pinMode(controller1[i], OUTPUT);
        pinMode(controller2[i], OUTPUT);
    }
    pinMode(MUX_A_OUT, INPUT);
    pinMode(MUX_B_OUT, INPUT);

    calibrate();
}


void LSArray::calibrate(){
    for (uint8_t i = 0; i < LS_NUM; i++){
        uint16_t calibrateValue = 0;

        for (uint8_t j = 0; j < LS_CALIBRATION_COUNT; j++){
            readSensor(i);
            calibrateValue += readValue[i];
        }

        threshold[i] = round((calibrateValue / (uint16_t)LS_CALIBRATION_COUNT) + LS_CALIBRATION_BUFFER);
    }
}


void LSArray::readSensor(uint8_t LSNum){
    uint8_t channel = pins[LSNum];
    bool mux1 = (channel < 16);
    channel = mux1 ? channel : channel - 16;

    for (uint8_t i = 0; i < 4; i++){
        uint8_t control = mux1 ? controller1[i] : controller2[i];
        digitalWriteFast(control, (channel >> i) & 0x1);
    }
    readValue[LSNum] = mux1 ? analogRead(MUX_A_OUT) : analogRead(MUX_B_OUT);
}


void LSArray::update(float _heading){
    heading = _heading;

    // Read Sensors and update onWhite state
    for (uint8_t i = 0; i < LS_NUM; i++){
        readSensor(i);
        onWhite[i] = (readValue[i] > threshold[i]);
    }

    // Updates onWhite state if others around it are
    for(uint8_t i = 0; i < LS_NUM; i ++) {
        if(!onWhite[i]) {
            if(onWhite[mod(i - 1, LS_NUM)] && onWhite[mod(i + 1, LS_NUM)]) {
                onWhite[i] = true;
            }
        }
    } 


    calculateLine();

}


void LSArray::calculateLine(){
    // Reset Variables
    bool active = 0;
    vectorX = 0;
    vectorY = 0;

    for (uint8_t i = 0; i < LS_NUM; i++){
        if (onWhite[i]){
            // If light sensor detects line add vector coords 
            active = 1;
            vectorX += sin(toRadians(450 - i * LS_NUM_MULTIPLIER));
            vectorY += cos(toRadians(450 - i * LS_NUM_MULTIPLIER));
        }
    }

    // Convert coords into angle if line visible
    vectorAngle = active ? mod(toDegrees(atan2(vectorY, vectorX)), 360) : NO_LINE_ANGLE;
}


void LSArray::calculateOutAvoidance(MoveData *calcMove){

}


bool LSArray::isOutsideLine(float angle){
    return false;
}


LineData LSArray::getLineData(){
    return data;
}