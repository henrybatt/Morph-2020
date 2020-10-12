#ifndef LIGHTARRAY_H
#define LIGHTARRAY_H

#include <Common.h>

#include <LineData.h>
#include <MoveData.h>

class LightArray{

    public:

         /* -- Class Constructor + Init -- */
        LightArray();

        /* -- Update onWhite State + Calculate line data + calculate return movements -- */
        void update();

        /* -- Return line data types -- */
        LineData getData();
        float getAngle();
        float getSize();

    private:

        /* -- Calibrate threshold values -- */
        void calibrate();

        /* -- Read light sensor and save recorded value -- */
        uint16_t readSensor(uint8_t index);

        LineData lineData = LineData();

        // uint8_t controller[5] = {LS_MUX_0, LS_MUX_1, LS_MUX_2, LS_MUX_3, LS_MUX_4}; // LS_MUX binary pins
        int controller1[4] = {MUX_A_0, MUX_A_1, MUX_A_2, MUX_A_3};  // MUX binary pins
        int controller2[4] = {MUX_B_0, MUX_B_1, MUX_B_2, MUX_B_3};
        uint8_t pins[LS_NUM] = {LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24, LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8}; // Multiplexer channels for each sensor (1-32)
        // uint8_t pins[LS_NUM] = {LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8, LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24};



        uint16_t threshold[LS_NUM] = {0}; // Threshold of field for each sensor
        bool onWhite[LS_NUM] = {0}; // If light sensor see white. If reading > threshold

};

extern LightArray lightArray;

#endif