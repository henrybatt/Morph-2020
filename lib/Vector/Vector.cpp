#include "Vector.h"


Vector::Vector(){
    getPolar(NO_VECTOR, NO_VECTOR);
}


Vector::Vector(float _x, float _y, bool cartesian){
    cartesian ? getPolar(_x, _y) : getCartesian(_x, _y);
}


void Vector::getPolar(float _i, float _j){
    i = _i;
    j = _j;

    arg = getArg(_i, _j);
    mag = getMag(_i, _j);
}


void Vector::getCartesian(float _arg, float _mag){
    arg = _arg;
    mag = _mag;

    i = getI(_arg, _mag);
    j = getJ(_arg, _mag); 
}


float Vector::getArg(float _i, float _j){
    return floatMod(90 - toDegrees(atan2(_j, _i)), 360);
}


float Vector::getMag(float _i, float _j){
    return sqrt(_i * _i + _j * _j);
}


float Vector::getI(float _arg, float _mag){
    return _mag * sinf(toRadians(_arg));
}


float Vector::getJ(float _arg, float _mag){
    return _mag * cosf(toRadians(_arg));
}


bool Vector::exists(){
    return mag!= 0;
}


bool Vector::between(float leftAngle, float rightAngle){
    return isAngleBetween(arg, leftAngle, rightAngle);
}


Vector Vector::operator+(Vector vector2){
    return Vector(i + vector2.i, j + vector2.j);
}


Vector Vector::operator-(Vector vector2){
    return Vector(i - vector2.i, j - vector2.j);
}


Vector Vector::operator*(float scalar){
    return Vector(arg, mag * scalar, false);
}


Vector Vector::operator/(float scalar){
    return Vector(arg, mag / scalar, false);
}


bool Vector::operator==(Vector vector2){
    return mag == vector2.mag;
}


bool Vector::operator!=(Vector vector2){
    return mag != vector2.mag;
}


bool Vector::operator<(Vector vector2){
    return mag < vector2.mag;
}


bool Vector::operator<=(Vector vector2){
    return mag <= vector2.mag;
}


bool Vector::operator>(Vector vector2){
    return mag > vector2.mag;
}


bool Vector::operator>=(Vector vector2){
    return mag >= vector2.mag;
}
