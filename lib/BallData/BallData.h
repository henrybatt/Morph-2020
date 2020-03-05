#ifndef BALLDATA_H
#define BALLDATA_H

#include <Common.h>

#include <Vector.h>

class BallData{

    public:

        /* -- Public variables + data -- */
        uint16_t angle = TSSP_NO_BALL_ANGLE; // Angle of ball
        uint8_t strength = TSSP_NO_BALL_STRENGTH; // Strength of ball
        bool isOut = false; // Ball is outside field
        float orbitAddition; // Orbit modifier angle
        Vector relativePosition = Vector(); // Relative ball position around robot
        Vector absPosition = Vector(); // Absolute postiion of ball on the field


        /* -- Default Class -- */
        BallData();

        /* -- Data import -- */
        BallData(uint16_t _angle, uint8_t _strength);

        /* -- Data import -- */
        BallData(uint16_t _angle, uint8_t _strength, bool isOut) : angle(_angle), strength(_strength), isOut(isOut) {}

        /* -- Orbit Angle addition -- */
        float orbitAngle();

        /* -- Ball is visible -- */
        bool visible();

        /* -- Return absolute position vector + calculate relavtive -- */
        Vector calcVectors(Vector robot, float heading);

        /* -- Return ball relative vector -- */
        Vector calcRelative(float heading);

        /* -- Operators -- */
        bool operator == (BallData ball2);
        bool operator != (BallData ball2);

};

#endif