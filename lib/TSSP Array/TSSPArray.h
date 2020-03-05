#ifndef TSSPARRAY_H
#define TSSPARRAY_H

#include <Common.h>

#include <BallData.h>

class TSSPArray{

    public:

        /* -- Class Constructor + Init -- */
        TSSPArray();

        /* -- Read from all TSSPS once -- */
        void read();

        /* -- Update + calculate data -- */
        void update();

        /* -- Return ball data types -- */
        BallData getData();
        uint16_t getAngle();
        uint8_t getStrength();

    private:

        BallData data = BallData(); // Ball Data

        uint8_t pins[TSSP_NUM] = {TSSP_PIN_1, TSSP_PIN_18, TSSP_PIN_17, TSSP_PIN_16, TSSP_PIN_15, TSSP_PIN_14, TSSP_PIN_13, TSSP_PIN_12, TSSP_PIN_11, TSSP_PIN_10, TSSP_PIN_9, TSSP_PIN_8, TSSP_PIN_7, TSSP_PIN_6, TSSP_PIN_5, TSSP_PIN_4, TSSP_PIN_3, TSSP_PIN_2};

        uint16_t values[TSSP_NUM] = {0};

        int8_t tsspAddition[TSSP_NUM] = {0};
        int8_t tsspAddition1[TSSP_NUM] = {0};
        int8_t tsspAddition0[TSSP_NUM] = {0};

        uint16_t readNum = 0;
};

extern TSSPArray tssps;

#endif