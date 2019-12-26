#include <MotorArray.h>

MotorArray motors = MotorArray();


MotorArray::MotorArray(){
    for (uint8_t i = 0; i < MOTOR_NUM; i++) {
        pinMode(ena[i], OUTPUT);
        pinMode(in1[i], OUTPUT);
        pinMode(in2[i], OUTPUT);
    }
}


void MotorArray::update(MoveData movement){

    #if DEBUG_MOVEMENT
        Serial.printf("Movement Debug: \t Angle: %i \t Speed: %i \t Correction: %i \n", movement.angle, movement.speed, movement.correction);
    #endif

    if (movement.speed != 0){

        #if ACCELERATION
            calculateAcceleration(&movement);
        #endif

        for (uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] = cosf(toRadians(motorAngle[i] + 90 - movement.angle));

        float scalar = fmax(fmax(fmax(abs(speeds[0]), abs(speeds[1])), abs(speeds[2])), abs(speeds[3]));
        for (uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] = round(speeds[i] * movement.speed / scalar) + movement.correction;

        scalar = fmax(fmax(fmax(abs(speeds[0]), abs(speeds[1])), abs(speeds[2])), abs(speeds[3]));
        for (uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] = round(speeds[i] * movement.speed / scalar);

    } else {
        for (uint8_t i = 0; i < MOTOR_NUM; i++) speeds[i] = movement.correction;
    }
    move();
}


void MotorArray::move(){
    for (uint8_t i = 0; i < MOTOR_NUM; i++){
        uint8_t enaWrite = 255;
        bool in1Write = false;
        bool in2Write = false;
        int16_t speed = speeds[i] * 2.55;

        if (speed != 0) {
            enaWrite = min(255, abs(speed));
            in1Write = reversed[i] ? speed < 0 : speed > 0;
            in2Write = !in1Write;
        }

        digitalWrite(in1[i], in1Write);
        digitalWrite(in2[i], in2Write);
        analogWrite(ena[i], enaWrite);
    }
}


void MotorArray::calculateAcceleration(MoveData *movement){
    Vector optimal = Vector(movement->angle, MAX_ACCELERATION * movement->speed / 100, false);
    Vector output = currentAcceleration + optimal;
    currentAcceleration = output * (1 - MAX_ACCELERATION);
    *movement = MoveData(output.arg, output.mag * 100);
}