#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID {
    public:
        PID(float p, float i, float d, float absoluteMax = 0.0f);
        float kp;
        float ki;
        float kd;
        float update(float input, float setpoint, float modulus = 0.0f);
    private:
        unsigned long lastTime;
        float lastError = 0;
        float absMax;
        float integral;
        float last;
};

#endif // PID_H