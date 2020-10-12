#include <LightArray.h>

LightArray lightArray = LightArray();


LightArray::LightArray(){
    // for (uint8_t i = 0; i < 5; i++) {
    //     pinMode(controller[i], OUTPUT);
    // }
    // pinMode(LS_MUX_OUT, INPUT);
    for (int i = 0; i < 4; i++) {
        pinMode(controller1[i], OUTPUT);
        pinMode(controller2[i], OUTPUT);
    }
    pinMode(MUX_A_OUT, INPUT);
    pinMode(MUX_B_OUT, INPUT);

    calibrate();
}

/* - Public - */

void LightArray::update(){
    /* - Update sensors - */

    // Read Sensors and update onWhite state
    for (uint8_t i = 0; i < LS_NUM; i++){
        onWhite[i] = readSensor(i) > threshold[i];
    }

    // Updates onWhite state if others around it are
    for (uint8_t i = 0; i < LS_NUM; i ++) {
        if(!onWhite[i]) {
            if(onWhite[mod(i - 1, LS_NUM)] && onWhite[mod(i + 1, LS_NUM)]) {
                onWhite[i] = true;
            }
        }
        #if DEBUG_LIGHT
            if (i == 0){
                Serial.print("Light Data:\t");
            }
            Serial.print(onWhite[i]);
            if ( i != LS_NUM - 1){
                Serial.print(" ");
            } else{
                Serial.println();
                delay(10);
            }
        #endif
    }

    /* - Clusters - */

    // Reset Values
    int8_t starts[4] = {-1, -1, -1, -1};
    int8_t ends[4] = {-1, -1, -1, -1};

    uint8_t numClusters = 0;
    bool findClusterStart = true;

    for (uint8_t i = 0; i < LS_NUM; i++){ // Loop through ls' to find clusters
        if (findClusterStart){ //Find first cluster value
            if (onWhite[i]){
                findClusterStart = false;
                starts[numClusters] = i;
                numClusters++;
            }
        } else { //Found start of cluster, find how many sensors
            if (!onWhite[i]){ // Cluster ended 1 ls ago
                findClusterStart = true;
                ends[numClusters - 1] = i - 1;
            }
        }
    }

     //If final light sensor sees white end cluster before, end last cluster
    if (onWhite[LS_NUM - 1]){
        ends[numClusters - 1] = LS_NUM -1;
    }
    
     // If first and last light sensor see line, merge both clusters together
    if (onWhite[0] && onWhite[LS_NUM - 1]){
        starts[0] = starts[numClusters - 1];
        starts[numClusters - 1] = -1;
        ends[numClusters - 1] = -1;
        numClusters -=  1;
    }

    /* - Calculate line - */
    if (numClusters > 0){
        float cluster1Angle = midAngleBetween(starts[0] * LS_NUM_MULTIPLIER, ends[0] * LS_NUM_MULTIPLIER);
        float cluster2Angle = midAngleBetween(starts[1] * LS_NUM_MULTIPLIER, ends[1] * LS_NUM_MULTIPLIER);
        float cluster3Angle = midAngleBetween(starts[2] * LS_NUM_MULTIPLIER, ends[2] * LS_NUM_MULTIPLIER);

        if (numClusters == 1){
            lineData.angle = cluster1Angle;
            lineData.size =  1 - cosf(toRadians(angleBetween(starts[0] * LS_NUM_MULTIPLIER, ends[0] * LS_NUM_MULTIPLIER) / 2.0f));

        } else if (numClusters == 2){
            lineData.angle = angleBetween(cluster1Angle, cluster2Angle) <= 180 ? midAngleBetween(cluster1Angle, cluster2Angle) : midAngleBetween(cluster2Angle, cluster1Angle);
            lineData.size =  1 - cosf(toRadians(angleBetween(cluster1Angle, cluster2Angle) <= 180 ? angleBetween(cluster1Angle, cluster2Angle) / 2.0f : angleBetween(cluster2Angle, cluster1Angle) / 2.0f));

        } else {
            float angleDiff12 = angleBetween(cluster1Angle, cluster2Angle);
            float angleDiff23 = angleBetween(cluster2Angle, cluster3Angle);
            float angleDiff31 = angleBetween(cluster3Angle, cluster1Angle);
            float biggestAngle = fmaxf(angleDiff12, fmaxf(angleDiff23, angleDiff31));
            if (biggestAngle == angleDiff12){
                lineData.angle = midAngleBetween(cluster2Angle, cluster1Angle);
                lineData.size =  angleBetween(cluster2Angle, cluster1Angle) <= 180 ? 1 - cosf(toRadians(angleBetween(cluster2Angle, cluster1Angle) / 2.0f)) : 1;
            } else if (biggestAngle == angleDiff23){
                lineData.angle = midAngleBetween(cluster3Angle, cluster2Angle);
                lineData.size =  angleBetween(cluster3Angle, cluster2Angle) <= 180 ? 1 - cosf(toRadians(angleBetween(cluster3Angle, cluster2Angle) / 2.0f)) : 1;
            } else {
                lineData.angle = midAngleBetween(cluster1Angle, cluster3Angle);
                lineData.size =  angleBetween(cluster1Angle, cluster3Angle) <= 180 ? 1 - cosf(toRadians(angleBetween(cluster1Angle, cluster3Angle) / 2.0f)) : 1;
            }
        }
    } else {
        lineData.angle = NO_LINE_ANGLE;
        lineData.size =  NO_LINE_SIZE;
    }

    #if DEBUG_LINE
        Serial.printf("Line lineData:\tAngle: %f,\tSize: %f \n", lineData.angle, lineData.size);
    #endif
}


LineData LightArray::getData(){
    return lineData;
}


float LightArray::getAngle(){
    return lineData.angle;
}


float LightArray::getSize(){
    return lineData.size;
}


/* - Private - */

void LightArray::calibrate(){
    for (uint8_t i = 0; i < LS_NUM; i++) {
        uint16_t calibrateValue = 0;

        for (uint8_t j = 0; j < LS_CALIBRATION_COUNT; j++) {
            calibrateValue += readSensor(i);
        }
        threshold[i] = roundf((calibrateValue / LS_CALIBRATION_COUNT) + LS_CALIBRATION_BUFFER);
    }
}


uint16_t LightArray::readSensor(uint8_t index) {
    //     for (uint8_t i = 0; i < 5; i++){
    //         digitalWriteFast(controller[i], (pins[index] >> i) & 0x1);
    //     }
    //     return analogRead(LS_MUX_OUT);
    // }
    // Read from sensor and return light value
    int channel = pins[index];
    bool mux1 = (channel < 16);
    channel = mux1 ? channel : channel - 16;
    for (int i = 0; i < 4; i++) {
        int control = mux1 ? controller1[i] : controller2[i];
        digitalWriteFast(control, channel >> i & 0x1);
    }
    return (mux1 ? analogRead(MUX_A_OUT) : analogRead(MUX_B_OUT));
}
