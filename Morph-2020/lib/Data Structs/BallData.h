#ifndef BALLDATA_H
#define BALLDATA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

#include <Vector.h>


class BallData{

    public:

        uint16_t angle;
        uint8_t strength;
        bool isOut;

        /* -- Initialise Empty Struct -- */
        BallData(){
            angle = TSSP_NO_BALL;
            strength = 0;
        }

        BallData(uint16_t angle, uint8_t strength) : angle(angle), strength(strength) {}

        BallData(uint16_t angle, uint8_t strength, bool isOut) : angle(angle), strength(strength), isOut(isOut) {}

        /* -- If ball is visible -- */
        bool visible(){
            return strength != 0;
        }

        /* -- Return Vector of Ball Coordinates -- */
        Vector vector(float heading = 0){
            return Vector(floatMod(angle + heading, 360), distance(), false);
        }


        /* -- Operators -- */
        bool operator == (BallData ball2){
            return angle == ball2.angle && strength == ball2.strength;
        }

        bool operator != (BallData ball2){
            return angle != ball2.angle || strength != ball2.strength;
        }



    private:

        double distance(){
            return 123;
        }

};

#endif