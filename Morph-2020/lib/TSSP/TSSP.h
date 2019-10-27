#ifndef TSSP_H
#define TSSP_H

#include <Arduino.h>
#include <Common.h>

#include <BallData.h>

class TSSP{
    public:

        TSSP() {}

        void init();
        void update();

        BallData data;
        BallData getBallData();

    private:

        void calculateAngleStrength(uint8_t n);

        uint16_t readValues[TSSP_NUM] = {0};
        uint16_t values[TSSP_NUM] = {0};
        uint16_t sortedValues[TSSP_NUM] = {0};
        uint8_t indexes[TSSP_NUM] = {0};

        int pins[TSSP_NUM] = {TSSP_PIN_1, TSSP_PIN_18, TSSP_PIN_17, TSSP_PIN_16, TSSP_PIN_15, TSSP_PIN_14, TSSP_PIN_13, TSSP_PIN_12, TSSP_PIN_11, TSSP_PIN_10, TSSP_PIN_9, TSSP_PIN_8, TSSP_PIN_7, TSSP_PIN_6, TSSP_PIN_5, TSSP_PIN_4, TSSP_PIN_3, TSSP_PIN_2};

        int tsspAddition[TSSP_NUM] = {0};
        int tsspAdditionA[TSSP_NUM];
        int tsspAdditionB[TSSP_NUM];

};

extern TSSP tssps;

#endif