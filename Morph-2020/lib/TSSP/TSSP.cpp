#include <TSSP.h>

void TSSP::init(){
    for (uint8_t i = 0; i < TSSP_NUM; i++){
        pinMode(pins[i], INPUT);
    }

    if (ROBOT){
        for (uint8_t i = 0; i < TSSP_NUM; i++) tsspAddition[i] = tsspAdditionA[i];
    } else {
        for (uint8_t i = 0; i < TSSP_NUM; i++) tsspAddition[i] = tsspAdditionB[i];
    }

}


void TSSP::update(){

    for (uint8_t i = 0; i < TSSP_READ_NUM; i++){
        for (uint8_t i = 0; i < TSSP_NUM; i++){
            readValues[i] += digitalReadFast(pins[i]) ^ 1;
        }
    }

    for (uint8_t i = 0; i < TSSP_NUM; i++){
        values[i] = (100 * readValues[i] / TSSP_READ_NUM) + tsspAddition[i];
        readValues[i] = 0;
        sortedValues[i] = 0;
        indexes[i] = 0;

        #if DEBUG_TSSP
            Serial.print(values[i]);
            if (i != TSSP_NUM - 1){
                Serial.print("\t");
            } else {
                Serial.println("");
            }
        #endif
    }

    for (uint8_t i = 0; i < TSSP_NUM; i++){
        for (uint8_t j = 0; j < TSSP_NUM; j++){
            if (values[i] > sortedValues[j]){
                if (j <= i){
                    ARRAYSHIFTDOWN(sortedValues, j, i);
                    ARRAYSHIFTDOWN(indexes, j, i);
                }
                sortedValues[j] = values[i];
                indexes[j] = i;
                break;
            }
        }
    }

    calculateAngleStrength(4);

}


void TSSP::calculateAngleStrength(uint8_t n){
    int8_t x = 0;
    int8_t y = 0;

    for (uint8_t i = 0; i < n; i++){
        x += sortedValues[i] * cos(toRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
        y += sortedValues[i] * sin(toRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
    }

    


}