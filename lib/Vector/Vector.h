#ifndef VECTOR_H
#define VECTOR_H

// 

#include "Common.h"


class Vector {

    public:

        /* -- I & J or Arg & Mag -- */
        Vector(float _x=0, float _y=0, bool cartesian=true);

        /* -- Vector Exists -- */
        bool exists();

        /* -- Vector is between two angles -- */
        bool between(float leftAngle, float rightAngle);

        float i, j;
        float arg, mag;


        /* -- Operators -- */
        Vector operator+(Vector vector2);
        Vector operator-(Vector vector2);
        Vector operator*(float scalar);
        Vector operator/(float scalar);

        bool operator==(Vector vector2);
        bool operator!=(Vector vector2);
        bool operator<(Vector vector2);
        bool operator<=(Vector vector2);
        bool operator>(Vector vector2);
        bool operator>=(Vector vector2);

    private:

        /* -- Calculate Argument -- */
        float getArg(float _i, float _j);

        /* -- Calculate magnitude -- */
        float getMag(float _i, float _j);

        /* -- Calculate I -- */
        float getI(float _arg, float _mag);

        /* -- Calculate J -- */
        float getJ(float _arg, float _mag);

        /* -- Convert to Polar -- */
        void getPolar(float _i, float _j);

        /* -- Convert to cartesian -- */
        void getCartesian(float _arg, float _mag);   

};


#endif