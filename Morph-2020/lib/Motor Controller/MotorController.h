#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>
#include <Common.h>

#include <MoveData.h>

class MotorController{

    public:
    
        MotorController() {}

        void init();
        void update(MoveData movement);

    private:

        void move();

        uint8_t ena[MOTOR_NUM] = {MOTOR_FRONT_RIGHT_ENA, MOTOR_BACK_RIGHT_ENA, MOTOR_BACK_LEFT_ENA, MOTOR_FRONT_LEFT_ENA};
        uint8_t in1[MOTOR_NUM] = {MOTOR_FRONT_RIGHT_IN1, MOTOR_BACK_RIGHT_IN1, MOTOR_BACK_LEFT_IN1, MOTOR_FRONT_LEFT_IN1};
        uint8_t in2[MOTOR_NUM] = {MOTOR_FRONT_RIGHT_IN2, MOTOR_BACK_RIGHT_IN2, MOTOR_BACK_LEFT_IN2, MOTOR_FRONT_LEFT_IN2};
        uint16_t motorAngle[MOTOR_NUM] = {MOTOR_FRONT_RIGHT_ANGLE, MOTOR_BACK_RIGHT_ANGLE, MOTOR_BACK_LEFT_ANGLE, MOTOR_FRONT_LEFT_ANGLE};
        bool reversed[MOTOR_NUM] = {MOTOR_FRONT_RIGHT_REVERSED, MOTOR_BACK_RIGHT_REVERSED, MOTOR_BACK_LEFT_REVERSED, MOTOR_FRONT_LEFT_REVERSED};

        float speeds[MOTOR_NUM] = {0};
    
};

extern MotorController motors;

#endif
