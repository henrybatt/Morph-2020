#include <MotorController.h>


MotorController motors = MotorController();


MotorController::MotorController(){
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
        for(uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] = round(speeds[i] * (movement.speed / maxVal)) + movement.correction; 

        maxVal = fmax(fmax(fmax(abs(speeds[0]), abs(speeds[1])), abs(speeds[2])), abs(speeds[3]));
        for(uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] = round(speeds[i] * (movement.speed / maxVal));
            
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
        int16_t speed = speeds[i] * 2.55;

        if (speed != 0){
            enaWrite = min(255, abs(speed));
            in1Write = reversed[i] ? speed < 0 : speed > 0;
            in2Write = !in1Write;
        }

        digitalWrite(in1[i], in1Write);
        digitalWrite(in2[i], in2Write);
        analogWrite(ena[i], enaWrite);
    }
}