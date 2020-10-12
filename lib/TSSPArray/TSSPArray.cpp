#include "TSSPArray.h"

float TSSP_ADD[TSSP_NUM] = {0};

TSSPArray tssp = TSSPArray();


TSSPArray::TSSPArray(){
    for (uint8_t i = 0; i < TSSP_NUM; i++) {
        pinMode(pins[i], INPUT);
    }
    reset();
}


void TSSPArray::read(){
    for (uint8_t i = 0; i < TSSP_NUM; i++) {
        values[i].mag += 1 - digitalReadFast(pins[i]);
    }
    readCounter++;
}


/* - Compare magnitudes of vectors in desc - */
static int cmp_mag(const void *p, const void *q){
    Vector a = *(const Vector *) p;
    Vector b = *(const Vector *) q;

    if (a.mag < b.mag){
        return 1;
    } else if (a.mag > b.mag){
        return -1;
    } else {
        return 1;
    }
}


void TSSPArray::update(){

    // Scale into unit vector
    for (uint8_t i = 0; i < TSSP_NUM; i++){
        values[i].mag = values[i].mag != 0 ? constrain((values[i].mag/readCounter) + TSSP_ADD[i], 0, 1) : 0;

        #if DEBUG_TSSP
            if (i == 0){ Serial.print("TSSP Data:\t"); }
            Serial.print(values[i].mag);
            if (i != TSSP_NUM - 1){
                Serial.print("\t");
            } else {
                Serial.println("");
            }
        #endif
    }

    //SORT VALUES
    qsort(values, TSSP_NUM, sizeof(Vector), cmp_mag);

    // Sum best values
    Vector summed = Vector();
    for (uint8_t i = 0; i < TSSP_NUM_CAL; i++){
        summed.i += values[i].mag * cosf(toRadians(-values[i].arg));
        summed.j += values[i].mag * sinf(toRadians(-values[i].arg));
    }

    // Convert to polar
    data.strength = 100 * sqrtf((summed.i*summed.i) + (summed.j*summed.j));
    data.angle = data.strength != 0 ? floatMod(360-toDegrees(atan2(summed.j, summed.i)), 360) : TSSP_NO_BALL_ANGLE;

    #if DEBUG_BALL_DATA
        Serial.printf("Ball Data:\tAngle: %i,\t Strength: %i \n", data.angle, data.strength);
    #endif

    reset();
}


void TSSPArray::reset(){
    for (uint8_t i = 0; i < TSSP_NUM; i++){
        values[i].mag = 0;
        values[i].arg = i * (360.0f/TSSP_NUM);
    }
    readCounter = 0;
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

