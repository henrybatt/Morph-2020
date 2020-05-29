#include <Avoidance.h>

Avoidance avoid = Avoidance();


Avoidance::Avoidance(){}


/* -- Public -- */

void Avoidance::data(BallData _ballData, LineData _lineData) {
    ballData = _ballData;
    lineData = _lineData;
}

MoveData Avoidance::update(MoveData calcMove, float heading) {
    /* - Calculate Avoidance - */

    bool onLine = (lineData.angle != NO_LINE_ANGLE);
    float lineAngle = onLine ? floatMod(lineData.angle + heading, 360.0f) : NO_LINE_ANGLE;
    float lineSize = onLine ? lineData.size : NO_LINE_SIZE;

    if (onLine) {
        // Seeing line determine how to return
        if (avoidData.onField()) {
            // Just saw line, save avoidData
            avoidData = LineData(lineAngle, lineSize);

        } else {
            if (avoidData.size == 3) {
                // Was outside of line but just started touching
                avoidData = LineData(floatMod(lineAngle + 180.0f, 360.0f), 2 - lineSize);

            } else {
                // Still on line, decide what side
                if (smallestAngleBetween(avoidData.angle, lineAngle) <= 90.0f) {
                    // Angles between 90 degrees, inside of field, save new angle
                    avoidData = LineData(lineAngle, lineSize);

                } else {
                    // Angle changed by more than 90 degrees, outside of field, modify angle
                    avoidData = LineData(floatMod(lineAngle + 180.0f, 360.0f), 2 - lineSize);
                }
            }
        }
    } else {
        if (!avoidData.onField()) {
            // No line but recently on
            if (avoidData.size <= 1) {
                // Was inside line, returned to field
                avoidData = LineData(NO_LINE_ANGLE, NO_LINE_SIZE);
            } else {
                // Was outside line, now over
                avoidData.size = 3;
            }
        }
    }

    #if DEBUG_AVOIDANCE
        Serial.printf("Avoid Data:\t Angle: %i,\t Size: %f \n", avoidData.angle, avoidData.size);
    #endif

    /* - Calculate Return Movememnt - */

    if (!avoidData.onField()) {
        float returnAngle = floatMod(avoidData.angle + 180.0f - heading, 360.0f);

        if (avoidData.size > LINE_SIZE_BIG) {
            return MoveData(returnAngle, (avoidData.size == 3 ? AVOID_OVER_SPEED : avoidData.size * AVOID_SPEED));

        } else if (avoidData.size > LINE_SIZE_SMALL) {
            if (isOutsideLine(ballData.angle, heading) && isOutsideLine(calcMove.angle, heading)) {
                // If ball and orbit is outside line
                return MoveData(-1, 0);

            } else if (avoidData.size > LINE_SIZE_MEDIUM) {
                if (smallestAngleBetween(calcMove.angle, returnAngle) < AVOID_BOUNCE_ANGLE) {
                    // If ball is within boucing angles decide if to move direct or bounce
                    if (smallestAngleBetween(calcMove.angle, returnAngle) < AVOID_NORMAL_ANGLE) {
                        // Withing direct return angle
                        return calcMove;
                    } else {
                        // Bounce towards ball
                        return MoveData(((floatMod(returnAngle + 180.0f - calcMove.angle, 360.0f)) > 0 && (floatMod(returnAngle + 180.0f - calcMove.angle, 360.0f)) < 180.0f)
                                            ? floatMod(returnAngle + 60.0f, 360.0f)
                                            : floatMod(returnAngle - 60.0f, 360.0f),
                                        avoidData.size * AVOID_BOUNCE_SPEED);
                    }
                }
            }
        }
    }

    return calcMove;
}


bool Avoidance::isOutsideLine(float angle, float heading) {
    if (!avoidData.onField()) {
        if (floatMod(avoidData.angle, 90.0f) > LINE_CORNER_ANGLE_THRESHOLD && floatMod(avoidData.angle, 90.0f) > 90.0f - LINE_CORNER_ANGLE_THRESHOLD) {
            // Must be on a corner if mod of angle greater than value line curves

            // If orbit angle and line angle between 90 or 180 respectively must be trying to move out
            return (angleIsInside(floatMod(avoidData.angle - 135 - LINE_BUFFER_CORNER, 360.0f), floatMod(avoidData.angle + 135.0f + LINE_BUFFER_CORNER, 360.0f), floatMod(angle + heading, 360.0f)));

        } else {
            // On side of line
            return (angleIsInside(floatMod(avoidData.angle - 90 - LINE_BUFFER, 360), floatMod(avoidData.angle + 135 + LINE_BUFFER, 360.0f), floatMod(angle + heading, 360.f)));
        }
    }

    return false;
}