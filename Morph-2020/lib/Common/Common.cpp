#include <Common.h>


float toDegrees(float rad){
    return rad*TO_DEGREES;
}


float toRadians(float deg){
    return deg*TO_RADIANS;
}


int mod(int value, int maxValue){
    int r = value % maxValue;
    return r < 0 ? r + maxValue : r;
}


float floatMod(float value, float maxValue){
    float r = fmod(value, maxValue);
	return r < 0 ? r + maxValue : r;
}


int findSign(float value){
    return value >= 0 ? 1 : -1;
}


bool isAngleBetween(float angle, float leftAngle, float rightAngle){
  if(rightAngle < leftAngle){
    return angle < rightAngle || angle > leftAngle;
  }
  else{
    return angle < rightAngle && angle > leftAngle;
  }
}


bool angleIsInside(float angleBoundCounterClockwise, float angleBoundClockwise, float angleCheck) {
    if (angleBoundCounterClockwise < angleBoundClockwise) {
        return (angleBoundCounterClockwise < angleCheck && angleCheck < angleBoundClockwise);
    } else {
        return (angleBoundCounterClockwise < angleCheck || angleCheck < angleBoundClockwise);
    }
}


float angleBetween(float angleCounterClockwise, float angleClockwise){
    return floatMod(angleClockwise - angleCounterClockwise, 360);
}


float smallestAngleBetween(float angleCounterClockwise, float angleClockwise){
    float ang = angleBetween(angleCounterClockwise, angleClockwise);
    return fmin(ang, 360 - ang);
}


float midAngleBetween(float angleCounterClockwise, float angleClockwise){
    return floatMod(angleCounterClockwise + angleBetween(angleCounterClockwise, angleClockwise) / 2.0, 360);
}



float distanceBetween(float x1, float x2, float y1, float y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


float updateMax(float max, float newVal){
    return max > newVal ? max : newVal;
}


float angleMap(float angle, float max) {
	while(angle >= max) {
		angle -= 360;
	}
	while(angle < (max-360)) {
		angle += 360;
	}
	return angle;
}