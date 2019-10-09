#include <Common.h>


double toDegrees(double rad){
    return rad*TO_DEGREES;
}


double toRadians(double deg){
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


double doubleMod(double value, double maxValue) {
    return fmod((value + maxValue), maxValue);
}


int findSign(double value){
    return value >= 0 ? 1 : -1;
}


bool isAngleBetween(double angle, double leftAngle, double rightAngle){
  if(rightAngle < leftAngle){
    return angle < rightAngle || angle > leftAngle;
  }
  else{
    return angle < rightAngle && angle > leftAngle;
  }
}


bool angleIsInside(double angleBoundCounterClockwise, double angleBoundClockwise, double angleCheck) {
    if (angleBoundCounterClockwise < angleBoundClockwise) {
        return (angleBoundCounterClockwise < angleCheck && angleCheck < angleBoundClockwise);
    } else {
        return (angleBoundCounterClockwise < angleCheck || angleCheck < angleBoundClockwise);
    }
}


double angleBetween(double angleCounterClockwise, double angleClockwise){
    return doubleMod(angleClockwise - angleCounterClockwise, 360);
}


double smallestAngleBetween(double angleCounterClockwise, double angleClockwise){
    double ang = angleBetween(angleCounterClockwise, angleClockwise);
    return fmin(ang, 360 - ang);
}


double midAngleBetween(double angleCounterClockwise, double angleClockwise){
    return mod(angleCounterClockwise + angleBetween(angleCounterClockwise, angleClockwise) / 2.0, 360);
}


double doubleAbs(double value){
    return value * findSign(value);
}


double distanceBetween(double x1, double x2, double y1, double y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


double updateMax(double max, double newVal){
    return max > newVal ? max : newVal;
}


double angleMap(double angle, double max) {
	while(angle >= max) {
		angle -= 360;
	}
	while(angle < (max-360)) {
		angle += 360;
	}
	return angle;
}