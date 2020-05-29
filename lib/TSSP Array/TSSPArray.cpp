#include <TSSPArray.h>

TSSPArray tssps = TSSPArray();

TSSPArray::TSSPArray(){
    for (uint8_t i = 0; i < TSSP_NUM; i++) {
        pinMode(pins[i], INPUT);
    }

    if (ROBOT) {
        for (uint8_t i = 0; i < TSSP_NUM; i++) {tsspAddition[i] = tsspAddition1[i];}
    } else {
        for (uint8_t i = 0; i < TSSP_NUM; i++) {tsspAddition[i] = tsspAddition0[i];}
    }


}

/* - Public - */


void TSSPArray::read(){

    for (uint8_t i = 0; i < TSSP_NUM; i++){
        values[i] += 1 - digitalReadFast(pins[i]);
    }

    readNum++;
}


void TSSPArray::update(){

    uint16_t sortedValues[TSSP_NUM] = {0};
    uint8_t indexes[TSSP_NUM] = {0};

    for (uint8_t i = 0; i < TSSP_NUM; i++){
        values[i] = values[i] != 0 ? (100 * values[i] / readNum) + tsspAddition[i] : 0;

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

    float x = 0;
    float y = 0;

    for (uint8_t i = 0; i < TSSP_NUM_CAL; i++) {
        x += sortedValues[i] * cosf(toRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
        y += sortedValues[i] * sinf(toRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
    }

    data.strength = sqrtf(powf(x, 2) + powf(y, 2));
    data.angle = data.strength != 0 ? floatMod(toDegrees(atan2f(y, x)), 360.0f) : TSSP_NO_BALL_ANGLE;

    #if DEBUG_BALL_DATA
        Serial.printf("Ball Data:\tAngle: %i,\t Strength: %i \n", data.angle, data.strength);
    #endif

    memset(values, 0, sizeof(values));
    readNum = 0;

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

