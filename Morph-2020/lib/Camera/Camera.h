#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Common.h>

#include <GoalData.h>


class Camera{
    public:

        /* -- Class Constructor + Init -- */
        Camera();

        /* -- Structures of goal data -- */
        GoalData attack;
        GoalData defend;

        /* -- Read Camera data and update angles and distances -- */
        void update();

        /* -- If goal's are visible faceGoal -- */
        void goalTrack();

        /* -- Find closest goal in pixels -- */
        uint8_t closestDistance();

        /* -- Find closest goal in centimeters -- */
        float closestCentimeter();

        /* -- If attacking goal closest -- */
        bool attackClosest();

        /* -- If a goal is visible -- */
        bool goalVisible();

        /* -- Determines if new data has come over cameraSerial -- */
        bool newData();

    private:

        /* -- Read from camera serial to get x & y values of goals -- */
        void read();

        bool newCamData;

};

extern Camera camera;

#endif