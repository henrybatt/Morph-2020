#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <math.h>

#include <Define.h>
#include <Debug.h>

#define PI 3.1415926535897932384626433832795
#define MATH_E 2.7182818284590452353602874713527

#define TO_RADIANS 0.01745329251994329576923690768489
#define TO_DEGREES 57.295779513082320876798154814105


double toDegrees(double rad);
double toRadians(double deg);

int mod(int value, int maxValue);
float floatMod(float value, float maxValue);
double doubleMod(double value, double maxValue);

int findSign(double value);

bool isAngleBetween(double angle, double leftAngle, double rightAngle);

bool angleIsInside(double angleBoundCounterClockwise, double angleBoundClockwise, double angleCheck);

double angleBetween(double angleCounterClockwise, double angleClockwise);
double smallestAngleBetween(double angle1, double angle2);
double midAngleBetween(double angleCounterClockwise, double angleClockwise);

double doubleAbs(double value);

double distanceBetween(double x1, double y1, double x2, double y2);
double updateMax(double max, double newVal);
double angleMap(double angle, double max);

#define ARRAYSHIFTDOWN(a, lower, upper){          \
    if (upper == (sizeof(a)/sizeof(a[0])) - 1){   \
        for (int q = upper - 1; q >= lower; q--){ \
            *(a + q + 1) = *(a + q); }            \
    } else{                                       \
        for (int q = upper; q >= lower; q--){     \
            *(a + q + 1) = *(a + q); }}}


// --- Structures --- //
struct Vector3D {
  double x;
  double y;
  double z;
};


#endif