#include <TSSP.h>


TSSP tssps = TSSP();


TSSP::TSSP(){
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
            if (ROBOT && (i == 5)) continue;
            readValues[i] += 1 - digitalReadFast(pins[i]);
        }
    }

    for (uint8_t i = 0; i < TSSP_NUM; i++){
        values[i] = readValues[i] == 0 ? 0 : 100 * readValues[i] / TSSP_READ_NUM + tsspAddition[i];
        readValues[i] = 0;
        sortedValues[i] = 0;
        indexes[i] = 0;

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

    calculateAngleStrength();

}


void TSSP::calculateAngleStrength(){
    int16_t x = 0;
    int16_t y = 0;

    for (uint8_t i = 0; i < 5; i++){
        x += sortedValues[i] * cos(toRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
        y += sortedValues[i] * sin(toRadians(indexes[i] * TSSP_NUM_MULTIPLIER));
    }

    data.strength = sqrtf(pow(x, 2) + pow(y, 2));
    data.angle = data.strength != 0 ? floatMod(toDegrees(atan2(y, x)), 360) : TSSP_NO_BALL_ANGLE;

    #if DEBUG_BALL_DATA
        Serial.printf("Ball Data:\tAngle: %i,\t Strength: %i \n", data.angle, data.strength);
    #endif

}


float TSSP::calculateAngleAddition(){
    float value = data.angle > 180 ? data.angle - 360 : data.angle;
    float ballAngleDifference = findSign(value) * fmin(90, 0.4 * expf(ANGLE_DIFF_MULTIPLIER * smallestAngleBetween(data.angle, 0)));
    float strengthFactor = constrain(((float)data.strength - (float)BALL_FAR_STRENGTH) / ((float)BALL_CLOSE_STRENGTH - (float)BALL_FAR_STRENGTH), 0, 1);
    float distanceMultiplier = constrain((0.02 * strengthFactor * expf( 4.5 * strengthFactor)), 0, 1);
    angleAddition = ballAngleDifference * distanceMultiplier;
    return angleAddition;
}


float TSSP::getAngleAddition(){
    return angleAddition;
}


BallData TSSP::getBallData(){
    return data;
}