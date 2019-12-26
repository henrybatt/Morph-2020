#include <TSSPArray.h>

TSSPArray tssps = TSSPArray();

TSSPArray::TSSPArray(){
    for (uint8_t i = 0; i < 5; i++) {
        pinMode(controller[i], OUTPUT);
    }
    pinMode(TSSP_MUX_OUT, INPUT);

    if (ROBOT) {
        for (uint8_t i = 0; i < TSSP_NUM; i++) tsspAddition[i] = tsspAdditionA[i];
    } else {
        for (uint8_t i = 0; i < TSSP_NUM; i++) tsspAddition[i] = tsspAdditionB[i];
    }
}

/* - Public - */

void TSSPArray::update(){

    uint16_t values[TSSP_NUM] = {0};
    uint16_t sortedValues[TSSP_NUM] = {0};
    uint8_t indexes[TSSP_NUM] = {0};

    for (uint8_t i = 0; i < TSSP_NUM; i++){
        changeChannel(i);
        for (uint8_t j = 0; j < TSSP_READ_NUM; j++){
            values[i] += 1 - digitalReadFast(TSSP_MUX_OUT);
        }

        values[i] = values[i] != 0 ? (100 * values[i] / TSSP_READ_NUM) + tsspAddition[i] : 0;

        #if DEBUG_TSSP
            if (i == 0){
                Serial.print("TSSP Data:\t");
            }
            Serial.print(values[i]);
            if (i != TSSP_NUM - 1){
                Serial.print("\t");
            } else {
                Serial.println("");
            }
        #endif
    }

    for (uint8_t i = 0; i < TSSP_NUM; i++) {
        for (uint8_t j = 0; j < TSSP_NUM; j++) {
            if (values[i] > sortedValues[j]) {
                if (j <= i) {
                    ARRAYSHIFTDOWN(sortedValues, j, i);
                    ARRAYSHIFTDOWN(indexes, j, i);
                }
                sortedValues[j] = values[i];
                indexes[j] = i;
                break;
            }
        }
    }

    int16_t x = 0;
    int16_t y = 0;

    for (uint8_t i = 0; i < 5; i++) {
        x += sortedValues[i] * cos(toRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
        y += sortedValues[i] * sin(toRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
    }

    data.strength = sqrtf(pow(x, 2) + pow(y, 2));
    data.angle = data.strength != 0 ? floatMod(toDegrees(atan2(y, x)), 360) : TSSP_NO_BALL_ANGLE;

    #if DEBUG_BALL_DATA
        Serial.printf("Ball Data:\tAngle: %i,\t Strength: %i \n", data.angle, data.strength);
    #endif
}


BallData TSSPArray::getData(){
    return data;
}


uint16_t TSSPArray::getAngle(){
    return data.angle;
}


uint8_t TSSPArray::getStrength(){
    return data.strength;
}

/* - Private - */

void TSSPArray::changeChannel(uint8_t index){
    for (uint8_t i = 0; i < 5; i++) {
        digitalWriteFast(controller[i], (pins[index] >> i) & 0x1);
    }
}