#ifndef MOTORARRAY_H
#define MOTORARRAY_H

#include <Arduino.h>

#include <MoveData.h>
#include <Vector.h>

class MotorArray{

    public:

        /* -- Class Constructor + Init -- */
        MotorArray();

        /* -- Calculate movement direction + move -- */
        void update(MoveData movement);

    private:

        /* -- Calculate acceleration along acceleration vector -- */
        void calculateAcceleration(MoveData *movement);

        uint8_t ena[MOTOR_NUM] = {MOTOR_FRONT_RIGHT_ENA, MOTOR_BACK_RIGHT_ENA, MOTOR_BACK_LEFT_ENA, MOTOR_FRONT_LEFT_ENA};
        uint8_t in1[MOTOR_NUM] = {MOTOR_FRONT_RIGHT_IN1, MOTOR_BACK_RIGHT_IN1, MOTOR_BACK_LEFT_IN1, MOTOR_FRONT_LEFT_IN1};
        uint8_t in2[MOTOR_NUM] = {MOTOR_FRONT_RIGHT_IN2, MOTOR_BACK_RIGHT_IN2, MOTOR_BACK_LEFT_IN2, MOTOR_FRONT_LEFT_IN2};
        uint16_t motorAngle[MOTOR_NUM] = {MOTOR_FRONT_RIGHT_ANGLE, MOTOR_BACK_RIGHT_ANGLE, MOTOR_BACK_LEFT_ANGLE, MOTOR_FRONT_LEFT_ANGLE};

        Vector currentAcceleration = Vector();
};

extern MotorArray motors;

#endif