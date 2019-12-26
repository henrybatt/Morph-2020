#ifndef TSSPARRAY_H
#define TSSPARRAY_H

#include <Common.h>

#include <BallData.h>

class TSSPArray{

    public:

        /* -- Class Constructor + Init -- */
        TSSPArray();

        /* -- Update + calculate data -- */
        void update();

        /* -- Return ball data types -- */
        BallData getData();
        uint16_t getAngle();
        uint8_t getStrength();

    private:

        /* -- Change MUX pin -- */
        void changeChannel(uint8_t index);

        BallData data; // Ball Data

        uint8_t controller[5] = {TSSP_MUX_0, TSSP_MUX_1, TSSP_MUX_2, TSSP_MUX_3, TSSP_MUX_4}; // TSSP MUX binary pins
        uint8_t pins[TSSP_NUM] = {TSSP_PIN_1, TSSP_PIN_18, TSSP_PIN_17, TSSP_PIN_16, TSSP_PIN_15, TSSP_PIN_14, TSSP_PIN_13, TSSP_PIN_12, TSSP_PIN_11, TSSP_PIN_10, TSSP_PIN_9, TSSP_PIN_8, TSSP_PIN_7, TSSP_PIN_6, TSSP_PIN_5, TSSP_PIN_4, TSSP_PIN_3, TSSP_PIN_2};

        int8_t tsspAddition[TSSP_NUM] = {0};
        int8_t tsspAdditionA[TSSP_NUM];
        int8_t tsspAdditionB[TSSP_NUM];


};

extern TSSPArray tssps;

#endif