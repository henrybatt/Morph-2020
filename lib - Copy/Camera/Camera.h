#ifndef CAMERA_H
#define CAMERA_H

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

        /* -- If a goal is visible -- */
        bool goalVisible();

        /* -- Find closest goal in pixels -- */
        uint8_t closestDistance();

        /* -- Find closest goal in centimeters -- */
        float closestCentimeter();

        /* -- If attacking goal closest -- */
        bool attackClosest();

        /* -- Determines if new data has come over cameraSerial -- */
        bool newData();

        bool faceGoal; // If we should face goal - goal visible + manual

    private:

        bool newCamData; // Update goal data this loop
};

extern Camera camera;

#endif