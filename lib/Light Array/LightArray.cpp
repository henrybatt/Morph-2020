#include <LightArray.h>

LightArray lightArray = LightArray();


LightArray::LightArray(){
    for (uint8_t i = 0; i < 5; i++) {
        pinMode(controller[i], OUTPUT);
    }
    pinMode(LS_MUX_OUT, INPUT);
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
    numClusters = 0;
    findClusterStart = true;

    for (int i = 0; i < 4; i++){
        starts[i] = -1;
        ends[i] = -1;
    }

    for (int i = 0; i < LS_NUM; i++){ // Loop through ls' to find clusters
        if (findClusterStart){ //Find first cluster value
            if (onWhite[i]){ 
                findClusterStart = false;
                starts[numClusters] = i;
                numClusters += 1;
            }
        } else { //Found start of cluster, find how many sensors
            if (!onWhite[i]){ // Cluster ended 1 ls ago
                findClusterStart = true;
                ends[numClusters - 1] = i - 1;
            }
        }
    }
     //If final light sensor sees white end cluster before, on last ls
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
            lineData.size =  1 - cos(toRadians(angleBetween(starts[0] * LS_NUM_MULTIPLIER, ends[0] * LS_NUM_MULTIPLIER) / 2.0));

        } else if (numClusters ==2){
            lineData.angle = angleBetween(cluster1Angle, cluster2Angle) <= 180 ? midAngleBetween(cluster1Angle, cluster2Angle) : midAngleBetween(cluster2Angle, cluster1Angle);
            lineData.size =  1 - cos(toRadians(angleBetween(cluster1Angle, cluster2Angle) <= 180 ? angleBetween(cluster1Angle, cluster2Angle) / 2.0 : angleBetween(cluster2Angle, cluster1Angle) / 2.0));

        } else {
            float angleDiff12 = angleBetween(cluster1Angle, cluster2Angle);
            float angleDiff23 = angleBetween(cluster2Angle, cluster3Angle);
            float angleDiff31 = angleBetween(cluster3Angle, cluster1Angle);
            float biggestAngle = max(angleDiff12, max(angleDiff23, angleDiff31));
            if (biggestAngle == angleDiff12){
                lineData.angle = midAngleBetween(cluster2Angle, cluster1Angle);
                lineData.size =  angleBetween(cluster2Angle, cluster1Angle) <= 180 ? 1 - cos(toRadians(angleBetween(cluster2Angle, cluster1Angle) / 2.0)) : 1;
            } else if (biggestAngle == angleDiff23){
                lineData.angle = midAngleBetween(cluster3Angle, cluster2Angle);
                lineData.size =  angleBetween(cluster3Angle, cluster2Angle) <= 180 ? 1 - cos(toRadians(angleBetween(cluster3Angle, cluster2Angle) / 2.0)) : 1;
            } else {
                lineData.angle = midAngleBetween(cluster1Angle, cluster3Angle);
                lineData.size =  angleBetween(cluster1Angle, cluster3Angle) <= 180 ? 1 - cos(toRadians(angleBetween(cluster1Angle, cluster3Angle) / 2.0)) : 1;
            }
        }
    } else {
        lineData.angle = NO_LINE_ANGLE;
        lineData.size =  NO_LINE_SIZE;
    }

    #if DEBUG_LINE
        Serial.printf("Line lineData:\tAngle: %i,\tSize: %f \n", lineData.angle, lineData.size);
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
        threshold[i] = round((calibrateValue / LS_CALIBRATION_COUNT) + LS_CALIBRATION_BUFFER);
    }
}


uint16_t LightArray::readSensor(uint8_t index) {
    for (uint8_t i = 0; i < 5; i++){
        digitalWriteFast(controller[i], (pins[index] >> i) & 0x1);
    }
    return analogRead(LS_MUX_OUT);
}


