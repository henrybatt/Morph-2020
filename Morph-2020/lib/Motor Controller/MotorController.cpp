#include <MotorController.h>

void MotorController::init(){
    for (uint8_t i = 0; i < MOTOR_NUM; i++){
        pinMode(ena[i], OUTPUT);
        pinMode(in1[i], OUTPUT);
        pinMode(in2[i], OUTPUT);
    }
}


void MotorController::update(MoveData movement){

    if (movement.speed != 0){

        for(uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] = cosf(toRadians(motorAngle[i] + 90 - movement.angle));         

        float maxVal = fmax(fmax(fmax(abs(speeds[0]), abs(speeds[1])), abs(speeds[2])), abs(speeds[3]));
        for(uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] = round(speeds[i] * (movement.speed / maxVal) + movement.correction); 

        maxVal = fmax(fmax(fmax(abs(speeds[0]), abs(speeds[1])), abs(speeds[2])), abs(speeds[3]));
        for(uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] *= (movement.speed / maxVal);
            
    } else {
        for(uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] = movement.correction;
    }

    move();

}


void MotorController::move(){
    for (uint8_t i = 0; i < MOTOR_NUM; i++){
        uint8_t enaWrite = 255;
        bool in1Write = false;
        bool in2Write = false;
        if (speeds[i] * 2.55 != 0){
            enaWrite = min(255, abs(speeds[i] * 2.55));
            in1Write = reversed[i] ? !(speeds[i] > 0) : speeds[i] > 0;
            in2Write = !in1Write;
        }
        digitalWrite(in1[i], in1Write);
        digitalWrite(in2[i], in2Write);
        analogWrite(ena[i], enaWrite);
    }
}