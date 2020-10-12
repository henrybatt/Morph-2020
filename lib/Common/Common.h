#ifndef COMMON_H
#define COMMON_H



#include <Arduino.h>
#include <math.h>

#include "Debug.h"
#include "Define.h"
#include "Pins.h"


#define PI 3.1415926535897932384626433832795
#define MATH_E 2.7182818284590452353602874713527

#define TO_RADIANS 0.01745329251994329576923690768489
#define TO_DEGREES 57.295779513082320876798154814105


float toDegrees(float rad);
float toRadians(float deg);

int mod(int value, int maxValue);
float floatMod(float value, float maxValue);

int sign(float value);

bool isAngleBetween(float angle, float leftAngle, float rightAngle);

bool angleIsInside(float angleBoundCounterClockwise, float angleBoundClockwise, float angleCheck);

float angleBetween(float angleCounterClockwise, float angleClockwise);
float smallestAngleBetween(float angle1, float angle2);
float midAngleBetween(float angleCounterClockwise, float angleClockwise);

float distanceBetween(float x1, float y1, float x2, float y2);
float updateMax(float max, float newVal);
float angleMap(float angle, float max);

void insertionSort(int *a, int n);
void insertionSortRev(int *a, int n);

bool lightgate_break();


#define ARRAYSHIFTDOWN(a, lower, upper){          \
    if (upper == (sizeof(a)/sizeof(a[0])) - 1){   \
        for (int q = upper - 1; q >= lower; q--){ \
            *(a + q + 1) = *(a + q); }            \
    } else{                                       \
        for (int q = upper; q >= lower; q--){     \
            *(a + q + 1) = *(a + q); }}}


#define SM_CHANGE_STATE_ATTACK(STATE) {sm.change_state(&Attack::STATE); return;}
#define SM_CHANGE_STATE_DEFEND(STATE) {sm.change_state(&Defence::STATE); return;}
#define SM_CHANGE_STATE_GLOBAL(STATE) {sm.change_state(&Global::STATE); return;}
#define SM_REVERT {sm.revert_state(); return;}
#define SM_MOTOR_BRAKE {robotState.movement.speed = 0; return;}

#define CENTER_COORD {Vector(IDLE_COORD_I, IDLE_COORD_J)}



// --- Structures --- //
struct Vector3D {
  float x;
  float y;
  float z;
};


#endif