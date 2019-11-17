#include <Avoidance.h>


Avoidance avoid = Avoidance();


Avoidance::Avoidance(){}


void Avoidance::update(LineData lightData, BallData _ballData, float _heading){

    ballData = _ballData;
    heading = _heading;

    bool onLine = (lightData.angle != NO_LINE_ANGLE);
    float lineAngle = onLine ? floatMod(lightData.angle + heading, 360) : NO_LINE_ANGLE;
    float lineSize = onLine ? lightData.size : NO_LINE_SIZE;

    if (onLine){
        // Seeing line determine how to return
        if (lineData.onField()){
            // Just saw line, save data
            lineData = LineData(lineAngle, lineSize);

        } else {
            if (lineData.size == 3){
                // Outside of line but just started touching
                lineData = LineData(floatMod(lineAngle + 180, 360), 2 - lineSize);

            } else {
                // Still on line, decide what side
                if (smallestAngleBetween(lineData.angle, lineAngle) <= 90){
                    // Angles between 90 degrees, inside of field, save new angle
                    lineData = LineData(lineAngle, lineSize);

                } else {
                    // Angle changed by more than 90 degrees, outside of field, modify angle
                    lineData = LineData(floatMod(lineAngle + 180, 360), 2 - lineSize);
                }
            }
        }
    } else {
        if (lineData.onField()){
            // No line but recently on
            if (lineData.size <= 1){
                // Was inside line, returned to field
                lineData = LineData(NO_LINE_ANGLE, NO_LINE_SIZE);
            } else {
                // Was outside line, now over
                lineData.size = 3;
            }
        }
    }

    #if DEBUG_AVOIDANCE
        Serial.printf("Avoid Data:\t Angle: %i,\t Size: %f \n", lineData.angle, lineData.size);
    #endif


}

MoveData Avoidance::calculateAvoidance(MoveData calcMove){
    float returnAngle = floatMod(lineData.angle + 180 - heading, 360);

    if (!lineData.onField()){
        // Not on the field, calculate return
        if ((lineData.size > LINE_SIZE_BIG) || (!ballData.visible() && lineData.size > LINE_SIZE_MEDIUM)){
            // Over other side of the line, move back across
            return MoveData(returnAngle, (lineData.size == 3 ? AVOID_OVER_SPEED : lineData.size * AVOID_SPEED));

        } else {
            // On inside on line, calculate bounce direction
            if (lineData.size > LINE_SIZE_SMALL && isOutsideLine(calcMove.angle)){
                // Ball is outside line, stop
                if (isOutsideLine(ballData.angle)){
                    return MoveData(-1, 0);
                } else {
                    return calculateAvoianceBounce(calcMove, returnAngle, lineData.size);
                }

            } else if(lineData.size > LINE_SIZE_MEDIUM){
                // Ball is inside field
                return calculateAvoianceBounce(calcMove, returnAngle, lineData.size);
            }
        }
    }
    return calcMove;
}


LineData Avoidance::getLineData(){
    return lineData;
}



MoveData Avoidance::calculateAvoianceBounce(MoveData calcMove, float returnAngle, float lineSize){

    if (smallestAngleBetween(calcMove.angle, returnAngle) < AVOID_BOUNCE_ANGLE){
    // If ball is within boucing angles decide if to move direct or bounce
        if (smallestAngleBetween(calcMove.angle, returnAngle) < AVOID_NORMAL_ANGLE){
            // Withing direct return angle
            return calcMove;
        }else{
            // Bounce towards ball
            return MoveData(calculateAvoianceBounceAngle(calcMove.angle, returnAngle), lineSize * AVOID_BOUNCE_SPEED);
        }
    }
    return calcMove;
}


float Avoidance::calculateAvoianceBounceAngle(float orbitAngle, float lineAngle){
    return ((floatMod(lineAngle + 180 - orbitAngle, 360)) > 0 && (floatMod(lineAngle + 180 - orbitAngle, 360)) < 180) 
                ? floatMod(lineAngle + 60, 360) : floatMod(lineAngle - 60, 360);
}


bool Avoidance::isOutsideLine(float angle){
    if (!lineData.onField()){
        if (floatMod(lineData.angle, 90) > LINE_CORNER_ANGLE_THRESHOLD && floatMod(lineData.angle, 90) > 90 - LINE_CORNER_ANGLE_THRESHOLD){
            // Must be on a corner if mod of angle greater than value line curves

            // If orbit angle and line angle between 90 or 180 respectively must be trying to move out
            return (angleIsInside(floatMod(lineData.angle - 135 - LINE_BUFFER_CORNER, 360), floatMod(lineData.angle + 135 + LINE_BUFFER_CORNER, 360), floatMod(angle + heading, 360)));
        } else {
            // On side of line
            return (angleIsInside(floatMod(lineData.angle - 90 - LINE_BUFFER, 360), floatMod(lineData.angle + 135 + LINE_BUFFER, 360), floatMod(angle + heading, 360)));
        }
    }
    return false;
}
