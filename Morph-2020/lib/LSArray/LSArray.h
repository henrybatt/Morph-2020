#ifndef LSARRAY_H
#define LSARRAY_H

#include <Arduino.h>
#include <Common.h>

#include <LineData.h>

class LSArray {

    public:

        /* -- Class Constructor + Init -- */
        LSArray();

        /* -- Update onWhite State -- */
        void update(float _heading);

        /* -- Calculate if ball is outside off line based off line angle and current orbit -- */
        bool isOutsideLine(float angle);

        void calculateAvoidanceData(LineData lightData);

        /* -- Return line data -- */
        LineData getLineData();

        /* -- Return Line Data -- */
        LineData getAvoidData();

    private:

        /* -- Calibrate threshold values -- */
        void calibrate();

        /* -- Read LS and save recorded value -- */
        void readSensor(uint8_t LSNum);

        /* -- Calculate angle + size of the line -- */
        void calculateLine();

        /* -- Calculate light sensor clusters -- */
        void calculateClusters();

        /* -- Structure of line data -- */
        LineData data;

        float heading;

        uint8_t controller1[4] = {MUX_A_0, MUX_A_1, MUX_A_2, MUX_A_3}; // MUX binary pins
        uint8_t controller2[4] = {MUX_B_0, MUX_B_1, MUX_B_2, MUX_B_3};
        uint8_t pins[LS_NUM] = {LS_7, LS_6, LS_5, LS_4, LS_3, LS_2, LS_1, LS_32, LS_31, LS_30, LS_29, LS_28, LS_27, LS_26, LS_25, LS_24, LS_23, LS_22, LS_21, LS_20, LS_19, LS_18, LS_17, LS_16, LS_15, LS_14, LS_13, LS_12, LS_11, LS_10, LS_9, LS_8}; // Multiplexer channels for each sensor (1-32)

        uint16_t threshold[LS_NUM] = {0}; // Threshold of field for each sensor
        uint16_t readValue[LS_NUM] = {0}; // Values read from each sensor
        bool onWhite[LS_NUM] = {0}; // If light sensor see white. If reading > threshold

        int starts[4]; // Array of cluster start indexes
        int ends[4];   // Array of cluster end indexes

        int numClusters = 0;   // Number of clusters found
        bool findClusterStart; // If cluster has begun

        float angle = NO_LINE_ANGLE;
        float size = NO_LINE_SIZE;

};

extern LSArray lightArray;

#endif