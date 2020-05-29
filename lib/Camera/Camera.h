#ifndef CAMERA_H
#define CAMERA_H

#include <Common.h>

#include <GoalData.h>
#include <Vector.h>

class Camera{

    public:

        /* -- Class Constructor + Init -- */
        Camera();

        /* -- Structures of goal data -- */
        GoalData attack;
        GoalData defend;

        /* -- Read Camera data and update angles and distances -- */
        Vector update(float heading);

    private:

        Vector robotPosition = Vector();
};

extern Camera camera;

#endif