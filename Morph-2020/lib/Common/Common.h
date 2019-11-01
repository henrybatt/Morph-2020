#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <math.h>

#include <Define.h>
#include <Pins.h>
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





/* --- PID --- */

#define HEADING_KP 0
#define HEADING_KI 0
#define HEADING_KD 0
#define HEADING_MAX_CORRECTION 255

#define ATTACK_GOAL_TRACK_KP 0
#define ATTACK_GOAL_TRACK_KI 0
#define ATTACK_GOAL_TRACK_KD 0
#define ATTACK_GOAL_TRACK_MAX_CORRECTION 255

#define DEFEND_GOAL_TRACK_KP 0
#define DEFEND_GOAL_TRACK_KI 0
#define DEFEND_GOAL_TRACK_KD 0
#define DEFEND_GOAL_TRACK_MAX_CORRECTION 255

#define X_MOVEMENT_KP 0
#define X_MOVEMENT_KI 0
#define X_MOVEMENT_KD 0
#define X_MOVEMENT_MAX 255

#define Y_MOVEMENT_KP 0
#define Y_MOVEMENT_KI 0
#define Y_MOVEMENT_KD 0
#define Y_MOVEMENT_MAX 255

#define TO_COORD_KP 4
#define TO_COORD_KI 0
#define TO_COORD_KD 0
#define TO_COORD_MAX_SPEED 100

#endif