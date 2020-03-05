#include <Avoidance.h>

Avoidance avoid = Avoidance();


Avoidance::Avoidance(){}


/* -- Public -- */

MoveData Avoidance::update(MoveData calcMove, LineData lineData, uint16_t ballAngle, float heading) {
    /* - Calculate Avoidance - */

    bool onLine = (lineData.angle != NO_LINE_ANGLE);
    float lineAngle = onLine ? floatMod(lineData.angle + heading, 360) : NO_LINE_ANGLE;
    float lineSize = onLine ? lineData.size : NO_LINE_SIZE;

    if (onLine) {
        // Seeing line determine how to return
        if (avoidData.onField()) {
            // Just saw line, save avoidData
            avoidData = LineData(lineAngle, lineSize);

        } else {
            if (avoidData.size == 3) {
                // Outside of line but just started touching
                avoidData = LineData(floatMod(lineAngle + 180, 360), 2 - lineSize);

            } else {
                // Still on line, decide what side
                if (smallestAngleBetween(avoidData.angle, lineAngle) <= 90) {
                    // Angles between 90 degrees, inside of field, save new angle
                    avoidData = LineData(lineAngle, lineSize);

                } else {
                    // Angle changed by more than 90 degrees, outside of field, modify angle
                    avoidData = LineData(floatMod(lineAngle + 180, 360), 2 - lineSize);
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
        float returnAngle = floatMod(avoidData.angle + 180 - heading, 360);

        if (avoidData.size > LINE_SIZE_BIG) {
            return MoveData(returnAngle, (avoidData.size == 3 ? AVOID_OVER_SPEED : avoidData.size * AVOID_SPEED));

        } else if (avoidData.size > LINE_SIZE_SMALL) {
            if (isOutsideLine(ballAngle, heading) && isOutsideLine(calcMove.angle, heading)) {
                return MoveData(-1, 0);

            } else if (avoidData.size > LINE_SIZE_MEDIUM) {
                if (smallestAngleBetween(calcMove.angle, returnAngle) < AVOID_BOUNCE_ANGLE) {
                    // If ball is within boucing angles decide if to move direct or bounce
                    if (smallestAngleBetween(calcMove.angle, returnAngle) < AVOID_NORMAL_ANGLE) {
                        // Withing direct return angle
                        return calcMove;
                    } else {
                        // Bounce towards ball
                        return MoveData(((floatMod(returnAngle + 180 - calcMove.angle, 360)) > 0 && (floatMod(returnAngle + 180 - calcMove.angle, 360)) < 180)
                                            ? floatMod(returnAngle + 60, 360)
                                            : floatMod(returnAngle - 60, 360),
                                        avoidData.size * AVOID_BOUNCE_SPEED);
                    }
                }
                return calcMove;
            }
        }
    }

    return calcMove;
}


bool Avoidance::isOutsideLine(float angle, float heading) {
    if (!avoidData.onField()) {
        if (floatMod(avoidData.angle, 90) > LINE_CORNER_ANGLE_THRESHOLD && floatMod(avoidData.angle, 90) > 90 - LINE_CORNER_ANGLE_THRESHOLD) {
            // Must be on a corner if mod of angle greater than value line curves

            // If orbit angle and line angle between 90 or 180 respectively must be trying to move out
            return (angleIsInside(floatMod(avoidData.angle - 135 - LINE_BUFFER_CORNER, 360), floatMod(avoidData.angle + 135 + LINE_BUFFER_CORNER, 360), floatMod(angle + heading, 360)));

        } else {
            // On side of line
            return (angleIsInside(floatMod(avoidData.angle - 90 - LINE_BUFFER, 360), floatMod(avoidData.angle + 135 + LINE_BUFFER, 360), floatMod(angle + heading, 360)));
        }
    }

    return false;
}